/*Uses distance to create a slider bar to indicate distance from the end of the level and the blackhole.*/
using UnityEngine.UI;
using UnityEngine;

public class SliderMechanism : MonoBehaviour
{
    public Slider PlayerProgressBar;
    public Slider bhProgressBar;

    private GameObject player;
    private GameObject endZone;
    private GameObject bh;

    void Start()
    {
        player = FindObjectOfType<PlayerControls>().gameObject;//Finds the positions of the player, blackhole and endgame.
        endZone = FindObjectOfType<EndCollision>().gameObject;
        bh = FindObjectOfType<BlackholeMovement>().gameObject;

        PlayerProgressBar.minValue = bh.transform.position.x;
        PlayerProgressBar.maxValue = endZone.transform.position.x;
        bhProgressBar.minValue = bh.transform.position.x;
        bhProgressBar.maxValue = endZone.transform.position.x;
    }


    void Update()
    {
        if (player != null)//if the player gameobject isnt null
        {
            PlayerProgressBar.value = player.transform.position.x;
        }
        bhProgressBar.value = bh.transform.position.x;
    }
}
