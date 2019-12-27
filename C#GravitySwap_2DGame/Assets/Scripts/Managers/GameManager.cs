/*A class to manage game events*/
using UnityEngine.SceneManagement;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance;
    public GameObject completeLevelUI;

    bool gameHasEnded = false;
    public float restartDelay = 1f;
    public float completeDelay = 2f;

    private void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
        }
        else
        {
            Destroy(gameObject);
            return;
        }
    }

    public void EndGame ()
    {
        if (gameHasEnded == false)
        {
            gameHasEnded = true;
            Debug.Log("Game Over");
            Invoke("Restart", restartDelay);//Invokes the method after a slight delay.
        }
    }

    public void CompleteLevel()
    {
        completeLevelUI.SetActive(true);//show the completed level UI
        Invoke("NextLevel", completeDelay);
    }

    public void Restart()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);//reload current scene
    }

    public void NextLevel()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);//load next scene in order of build index.
    }
}
