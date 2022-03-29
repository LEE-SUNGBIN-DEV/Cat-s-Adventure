#pragma once

class GameObject;
class GameScene;

void CreateGameObject(GameObject* _gameObject, OBJECT_TYPE _objectType);
void RemoveGameObject(GameObject* _gameObject);
void ChangeGameScene(SCENE_TYPE _sceneType);

template<typename _type>
void RemoveVector(vector<_type>& _vector)
{
	for (size_t i = 0; i < _vector.size(); ++i)
	{
		if (_vector[i] != nullptr)
		{
			delete _vector[i];
		}
	}
	_vector.clear();
}

template<typename _key, typename _type>
void RemoveMap(map<_key, _type>& _map)
{
	typename map<_key, _type>::iterator iter = _map.begin();

	for (; iter != _map.end(); ++iter)
	{
		if (iter->second != nullptr)
		{
			delete iter->second;
		}
	}
	_map.clear();
}