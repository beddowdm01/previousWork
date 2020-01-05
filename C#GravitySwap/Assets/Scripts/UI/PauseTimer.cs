/*keeps the game paused at the start of levels*/
using UnityEngine.UI;
using UnityEngine;

public class PauseTimer : MonoBehaviour
{
    public static bool PauseTimerActive = false;
    public Text timerText;
    public float timer = 3f;

    [SerializeField]
    private GameObject pauseTimer = null;

    private bool finishedCount = false;

    void Awake()
    {
        StartTimer(3f);
    }

    void Update()
    {
        if (pauseTimer.activeInHierarchy == true && PauseTimerActive)
        {
            Time.timeScale = 0f;
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
        PauseTimerActive = false;
        PlayerMovement.Instance.InputsEnabled = true;
    }
    
    public void StartTimer(float time)
    {
        timer = time;
        pauseTimer.SetActive(true);
        Time.timeScale = 0f;
        PauseTimerActive = true;
        PlayerMovement.Instance.InputsEnabled = false;
    }
}
