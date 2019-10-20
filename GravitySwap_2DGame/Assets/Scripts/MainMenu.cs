﻿//A class to handle all main menu buttons
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using UnityEngine;

public class MainMenu : MonoBehaviour
{
    public GameObject levelSelect;
    public GameObject main;
    // Start is called before the first frame update
    public void StartGame()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }
    public void SelectLevel()
    {
        if (levelSelect && main)
        {
            levelSelect.SetActive(true);
            main.SetActive(false);
        }
    }

}
