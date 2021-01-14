using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

[CustomEditor(typeof(LevelCollection))]
public class LevelCollectionEditor : Editor
{
    Object obj = null;

    public override void OnInspectorGUI()
    {
        base.OnInspectorGUI();
        
        obj = EditorGUILayout.ObjectField("Scene Asset", obj, typeof(SceneAsset), false);
        if (GUILayout.Button("Add Scene"))
        {
            LevelCollection levelCollection = (LevelCollection)target;
            SceneReference sceneReference = new SceneReference();
            sceneReference.ScenePath = AssetDatabase.GetAssetPath(obj.GetInstanceID());
            levelCollection.myScenes.Add(sceneReference);          
        }
    }
}
