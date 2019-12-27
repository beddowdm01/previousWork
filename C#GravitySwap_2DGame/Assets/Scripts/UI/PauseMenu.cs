/*A class for the pausemenu in the game*/
using UnityEngine.UI;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PauseMenu : MonoBehaviour
{
    public static bool GameIsPaused = false;

    [SerializeField]
    private int mainMenuIndex = 0;
    [SerializeField]
    private GameObject pauseMainPanel = null;
    [SerializeField]
    private GameObject pauseOptionsPanel = null;
    [SerializeField]
    private GameObject levelSelectPanel = null;
    [SerializeField]
    private Slider masterVolumeSlider = null;

    private bool isPaused;
    private bool isFullScreen;
    private int selectedLevelIndex = 0;


    private void Start()
    {
        masterVolumeSlider.value = AudioManager.Instance.MasterVolume;//sets the master volume slider
        Screen.SetResolution(Screen.currentResolution.width, Screen.currentResolution.height, isFullScreen);//sets the resolution
        Resume();
    }

    void Update()
    {
        if (isFullScreen != Screen.fullScreen)
        {
            isFullScreen = Screen.fullScreen;
        }
        if (Input.GetKeyDown(KeyCode.P) || Input.GetKeyDown(KeyCode.Escape) && PauseTimer.PauseTimerActive == false)//if espace is clicked
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
        pauseMainPanel.SetActive(false);
        Time.timeScale = 1f;
        GameIsPaused = false;
        PlayerMovement.Instance.InputsEnabled = true;
    }

    public void Pause()//Method to pause the game
    {
        pauseMainPanel.SetActive(true);
        Time.timeScale = 0f;
        GameIsPaused = true;
    }

    public void MusicSliderChanged(Slider slider)//changes music volume
    {
        AudioManager.Instance.ChangeAudioVolume(slider.value, Sound.Type.Music);
    }

    public void EffectsSliderChanged(Slider slider)
    {
        AudioManager.Instance.ChangeAudioVolume(slider.value, Sound.Type.Effects);
    }

    public void MasterSliderChanged(Slider slider)
    {
        AudioManager.Instance.ChangeMasterVolume(slider.value);
    }

    public void Quit()//Method to quit the game
    {
        SceneManager.LoadScene(mainMenuIndex);
    }


    public void ShowOptionsMenu()
    {
        pauseMainPanel.SetActive(false);
        pauseOptionsPanel.SetActive(true);
    }

    public void HideOptionsMenu()
    {
        pauseMainPanel.SetActive(true);
        pauseOptionsPanel.SetActive(false);
    }

    public void ShowLevelSelect()
    {
        levelSelectPanel.SetActive(true);
        pauseMainPanel.SetActive(false);
    }

    public void HideLevelSelect()
    {
        pauseMainPanel.SetActive(true);
        levelSelectPanel.SetActive(false);
    }

    public void SelectLevelDropdown(Dropdown dropdown)
    {
        selectedLevelIndex = dropdown.value;
    }

    public void OpenLevel()
    {
        SceneManager.LoadScene((selectedLevelIndex * 2) + 1);
    }

    public void ChangeFullScreen(Toggle toggle)
    {
        Screen.SetResolution(Screen.currentResolution.width, Screen.currentResolution.height, toggle.isOn);
    }

    public void ChangeResolution(Dropdown dropdown)
    {
        int choiceIndex = dropdown.value;
        Debug.Log(choiceIndex);
        if (choiceIndex == 0)
        {
            Screen.SetResolution(1920, 1080, Screen.fullScreen);
        }
        if (choiceIndex == 1)
        {
            Screen.SetResolution(1280, 720, Screen.fullScreen);
        }
        if (choiceIndex == 2)
        {
            Screen.SetResolution(1024, 576, Screen.fullScreen);
        }
    }
}
