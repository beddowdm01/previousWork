/*keeps the game paused at the start of levels*/
using UnityEngine.UI;
using UnityEngine;

public class PauseTimer : MonoBehaviour
{
    public static bool GameIsPaused = false;
    public Text timerText;
    public float timer = 3f;
    public GameObject pauseTimer;

    private bool finishedCount = false;

    void Awake()
    {
        startTimer();
    }

    void Update()
    {
        if (pauseTimer.activeInHierarchy == true)
        {
            timer -= Time.unscaledDeltaTime;//uses unscaled time to count down timer during pause.
            timerText.text = timer.ToString("0");
            if (timer <= 0 && finishedCount == false)
            {
                Resume();
                finishedCount = true;
            }
        }
    }

    void Resume()
    {
        pauseTimer.SetActive(false);
        Time.timeScale = 1f;
        GameIsPaused = false;
    }
    
    void startTimer()
    {
        pauseTimer.SetActive(true);
        Time.timeScale = 0f;
        GameIsPaused = true;
    }
}
