using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class SelectLevel : MonoBehaviour
{
    // Start is called before the first frame update
    public GameObject prevMenu;
    public GameObject levelSelect;
    public Dropdown myDropDownMenu;

    public void CloseLevelSelect()
    {
        if (levelSelect && prevMenu)
        {
            levelSelect.SetActive(false);
            prevMenu.SetActive(true);
        }
    }

    void Start()//Assign listener to the dropdown on start
    {
        myDropDownMenu.onValueChanged.AddListener(delegate {
            myDropdownValueChangedHandler(myDropDownMenu);
        });
    }

    private void myDropdownValueChangedHandler(Dropdown target)//when its changed
    {
        Debug.Log("selected: " + target.value);
    }

    public void SetDropdownIndex(int index)
    {
        myDropDownMenu.value = index;
    }

    public void OpenLevel()
    {
        SceneManager.LoadScene((myDropDownMenu.value * 2) + 1);
    }
}
