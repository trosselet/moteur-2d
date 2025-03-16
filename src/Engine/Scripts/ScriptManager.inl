#pragma once

template <typename SType>
void ScriptManager::CreateScript(Entity* entity)
{
    SType* script = new SType();
    script->SetOwner(entity);
    scriptedEntityToAdd[entity->GetIndex()].push_back(script);
}