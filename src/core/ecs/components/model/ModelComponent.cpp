#include "ModelComponent.h"
#include "imgui/imgui/imgui.h"
#include "core/ecs/components/TransformComponent.h"
#include "core/os/FileDialogue.h"
#include "core/renderer/Texture.h"

#define MAX_MESHES 10

Vivid::ModelComponent::ModelComponent()
{
	m_Meshes.reserve(MAX_MESHES);
}

void Vivid::ModelComponent::Draw(Camera* camera)
{
	glm::mat4 transform = m_Entity->GetComponent<Vivid::TransformComponent>()->GetTransform();

	for (auto& mesh : m_Meshes)
	{
		mesh->Update(transform);
		mesh->Draw(camera);
	}
}

void Vivid::ModelComponent::AddMesh(Vivid::Mesh* mesh)
{
	m_Meshes.push_back(mesh);
}

void Vivid::ModelComponent::RemoveMesh(Vivid::Mesh* mesh)
{
	m_Meshes.erase(std::remove(m_Meshes.begin(), m_Meshes.end(), mesh), m_Meshes.end());
}


//void Vivid::ModelComponent::ImGuiRender()
//{
//	ImGui::SeparatorText("Meshes");
//
//	static ImGuiTableFlags flags =
//	    ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable
//	    | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
//	    | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_NoBordersInBody
//	    | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY
//	    | ImGuiTableFlags_SizingFixedFit;
//	static ImGuiTableColumnFlags columns_base_flags = ImGuiTableColumnFlags_None;
//
//
//	if (ImGui::BeginTable("Meshes", 3, flags, ImVec2(0, 0), 0))
//	{
//		static bool items_need_sort = false;
//		// Declare columns
//		// We use the "user_id" parameter of TableSetupColumn() to specify a user id that will be stored in the sort specifications.
//		// This is so our sort function can identify a column given our own identifier. We could also identify them based on their index!
//		ImGui::TableSetupColumn("ID", columns_base_flags | ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoHide, 0.0f, 0);
//		ImGui::TableSetupColumn("Action", columns_base_flags | ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, 1);
//		ImGui::TableSetupColumn("Hidden", columns_base_flags | ImGuiTableColumnFlags_DefaultHide | ImGuiTableColumnFlags_NoSort);
//
//		for (int row_n = 0; row_n < m_Meshes.size(); row_n++)
//		{
//			Mesh* mesh = m_Meshes[row_n];
//			ImGui::PushID(mesh->GetID());
//			ImGui::TableNextRow(ImGuiTableRowFlags_None, 10);
//			if (ImGui::TableSetColumnIndex(0))
//			{
//				ImGui::Text("%d", mesh->GetID());
//			}
//			if (ImGui::TableSetColumnIndex(1))
//			{
//				if (ImGui::ImageButton((ImTextureID)texMinus->getRendererID(), ImVec2(100, 100)))
//				{
//					RemoveMesh(mesh);
//				}
//			}
//			ImGui::PopID();
//
//		}
//
//		ImGui::EndTable();
//	}
//}

namespace
{
enum MyItemColumnID
{
	MyItemColumnID_ID,
	MyItemColumnID_Action,
	MyItemColumnID_Description
};

struct MyItem
{
	int         ID;
	const char* Name;
	int         Quantity;
};

static const ImGuiTableSortSpecs* s_current_sort_specs = NULL;
}

void Vivid::ModelComponent::ImGuiRender()
{
	static const char* template_items_names[] =
	{
		"Banana", "Apple", "Cherry", "Watermelon", "Grapefruit", "Strawberry", "Blueberry", "Orange", "Plum", "Coconut"
	};
	const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
	const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;
	static ImGuiTableFlags flags =
	    ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable
	    | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
	    | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_NoBordersInBody
	    | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY
	    | ImGuiTableFlags_SizingFixedFit;
	static ImGuiTableColumnFlags columns_base_flags = ImGuiTableColumnFlags_None;

	enum ContentsType { CT_Text, CT_Button, CT_SmallButton, CT_FillButton, CT_Selectable, CT_SelectableSpanRow };
	static int contents_type = CT_SelectableSpanRow;
	const char* contents_type_names[] = { "Text", "Button", "SmallButton", "FillButton", "Selectable", "Selectable (span row)" };
	static int freeze_cols = 1;
	static int freeze_rows = 1;
	static int items_count = IM_ARRAYSIZE(template_items_names) * 2;
	static ImVec2 outer_size_value = ImVec2(0.0f, TEXT_BASE_HEIGHT * 12);
	static float row_min_height = 0.0f; // Auto
	static float inner_width_with_scroll = 0.0f; // Auto-extend
	static bool outer_size_enabled = true;
	static bool show_headers = true;
	static bool show_wrapped_text = false;

	static ImVector<int> selection;

	const ImDrawList* parent_draw_list = ImGui::GetWindowDrawList();
	const float inner_width_to_use = (flags & ImGuiTableFlags_ScrollX) ? inner_width_with_scroll : 0.0f;
	if (ImGui::BeginTable("table_advanced", 3, flags, outer_size_enabled ? outer_size_value : ImVec2(0, 0), inner_width_to_use))
	{
		// Declare columns
		// We use the "user_id" parameter of TableSetupColumn() to specify a user id that will be stored in the sort specifications.
		// This is so our sort function can identify a column given our own identifier. We could also identify them based on their index!
		ImGui::TableSetupColumn("ID",           columns_base_flags | ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoHide, 0.0f, MyItemColumnID_ID);
		ImGui::TableSetupColumn("Action",       columns_base_flags | ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Action);
		ImGui::TableSetupScrollFreeze(freeze_cols, freeze_rows);

		// Take note of whether we are currently sorting based on the Quantity field,
		// we will use this to trigger sorting when we know the data of this column has been modified.
		const bool sorts_specs_using_quantity = (ImGui::TableGetColumnFlags(3) & ImGuiTableColumnFlags_IsSorted) != 0;

		ImGui::PushButtonRepeat(true);
		ImGuiListClipper clipper;
		clipper.Begin(m_Meshes.size());
		while (clipper.Step())
		{
			for (int row_n = clipper.DisplayStart; row_n < clipper.DisplayEnd; row_n++)
			{
				if (row_n >= m_Meshes.size())
					break;
				Mesh* item = m_Meshes[row_n];
				//if (!filter.PassFilter(item->Name))
				//    continue;

				const bool item_is_selected = selection.contains(item->GetID());
				ImGui::PushID(item->GetID());
				ImGui::TableNextRow(ImGuiTableRowFlags_None, row_min_height);

				// For the demo purpose we can select among different type of items submitted in the first column
				ImGui::TableSetColumnIndex(0);
				char label[32];
				sprintf(label, "%04d", item->GetID());

				ImGuiSelectableFlags selectable_flags = (contents_type == CT_SelectableSpanRow) ? ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap : ImGuiSelectableFlags_None;
				if (ImGui::Selectable(label, item_is_selected, selectable_flags, ImVec2(0, row_min_height)))
				{
					if (ImGui::GetIO().KeyCtrl)
					{
						if (item_is_selected)
							selection.find_erase_unsorted(item->GetID());
						else
							selection.push_back(item->GetID());
					}
					else
					{
						selection.clear();
						selection.push_back(item->GetID());
					}
				}

				if (ImGui::TableSetColumnIndex(1))
				{
					if (ImGui::ImageButton((ImTextureID)texMinus->getRendererID(), ImVec2(10, 10),
					        ImVec2(0.25, 0.25), ImVec2(0.75, 0.75), 2))
					{
						RemoveMesh(m_Meshes[row_n]);
					}
				}

				ImGui::PopID();
			}
		}
		ImGui::PopButtonRepeat();

		// Store some info to display debug details below
		ImGui::EndTable();
	}
}