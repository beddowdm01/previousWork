/*A class for the pausemenu in the game*/
using UnityEngine.UI;
using UnityEngine;

public class PauseMenu : MonoBehaviour
{
    public static bool GameIsPaused = false;
    public GameObject pauseScreen;



    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))//if espace is clicked
        {
            if (GameIsPaused == true)//if it was already paused
            {
                Resume();
            }
            else//otherwise pause the game
            {
                Pause();
            }
        }
    }

    public void Resume()//Method to resume the game
    {
        pauseScreen.SetActive(false);
        Time.timeScale = 1f;
        GameIsPaused = false;
    }

    public void Pause()//Method to pause the game
    {
        pauseScreen.SetActive(true);
        Time.timeScale = 0f;
        GameIsPaused = true;
    }

    public void Quit()//Method to quit the game
    {
        Application.Quit();
    }
}
