# ECS API
## Introduction
The ECS API is a way to create 3D scenes in Vivid. It is a way to create entities and 
components. 

**Do not create entities and components directly. Use the ECS API to create them.**

## Creation
### Entity
Entites are the main objects in the ECS API. They are the objects that are rendered in the scene.
To create an entity you can use the `Entity` class. 

```cpp
Ref<Entity> entity = ECS::CreateEntity("Entity Name");
```

ECS is a namespace in the Vivid library, it contains all the helper functions to maintain all the entities and 
components.

### Component
Components are the objects that are attached to entities. They are the objects that define the 
properties of the entity. 

To create a component you can use the `Component` class.

```cpp
Ref<Component> component = ECS::CreateComponent<ExampleComponent>();
```

Only components that inherit from the `Component` class can created using the `CreateComponent` function.

## Adding Components to Entities
To add a component to an entity you can use the `AddComponent` function in the ECS namespace.

```cpp
ECS::AddComponent(entityID, componentID);
```

To get the entityID you can use the `GetEntityID` method in the entity class, and to get the 
componentID you can use the `GetComponentID` method in the component class.

## Getting Components
To get a component from an entity you can use the `GetComponent` function in the ECS namespace.

```cpp
Ref<Component> component = ECS::GetComponent(componentType, entityID);
```

You can also get all the components of a certain type from the entity using the `GetComponents` function.

```cpp
Vector<Vivid::DirectionalLightComponent*> directionalLights;
Vivid::ECS::GetAllComponents(Vivid::ComponentType::DirectionalLightComponent, directionalLights);
```

## UI
All these tasks can also be done using the UI.
