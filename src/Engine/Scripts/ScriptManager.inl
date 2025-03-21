#pragma once

template <typename SType, typename ... Args>
SType* ScriptManager::CreateScript(Entity* entity, Args&&... args)
{
    SType* script = new SType(std::forward<Args>(args)...);
    script->SetOwner(entity);
    scriptedEntityToAdd[entity->GetIndex()].push_back(script);
    return script;
}