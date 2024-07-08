public class LevelManager : MonoBehaviour
{
    // List of scenes to choose from for gameplay.
    private List<string> scenesToChooseFrom = new List<string>();
    private string nextLevel;

    // Generates a list of scenes based on the configuration.
    public void LoadScenesList()
    {
        // ... [Other implementations]
        // Removes unwanted scenes.
        foreach (string scene in scenesToRemove)
        {
            scenesToChooseFrom.Remove(scene);
        }
    }

    // Loads the next scene, either randomly or in numerical order.
    public void LoadNextScene()
    {
        // ... [Other implementations]
        if (playingScenesOrder == WhichOrderToPlayScenes.Random)
        {
            LoadNextSceneInRandomOrder();
        }
        else if (playingScenesOrder == WhichOrderToPlayScenes.NumiricalOrder)
        {
            LoadNextSceneInNumericalOrder();
        }
        // ... [Other implementations]
    }

    // Helper function to load the next scene in a numerical order.
    private string LoadNextSceneInNumericalOrder()
    {
        nextLevel = scenesToChooseFrom.ElementAt(0);
        scenesToChooseFrom.RemoveAt(0);
        return nextLevel;
    }

    // Helper function to load the next scene randomly.
    private string LoadNextSceneInRandomOrder()
    {
        int randomNumber = Random.Range(0, scenesToChooseFrom.Count);
        nextLevel = scenesToChooseFrom.ElementAt(randomNumber);
        scenesToChooseFrom.RemoveAt(randomNumber);
        return nextLevel;
    }

    // ... [Other methods]
}