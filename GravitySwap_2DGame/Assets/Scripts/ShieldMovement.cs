/*Moves the shield sprite with the player*/
using UnityEngine;

public class ShieldMovement : MonoBehaviour
{
    private PlayerControls player;
    public float xOffset = 2;
    public float yOffset = 0;

    private Vector3 shieldOffset;
    // Update is called once per frame

    private void Start()//set the player variable
    {
        player = FindObjectOfType<PlayerControls>();
    }

    void Update()
    {
        if (player != null)//if player gameobject is active
        {
            shieldOffset = new Vector3(player.transform.position.x + xOffset, player.transform.position.y + yOffset, 0);//create a vector that is offset from the player
            transform.position = shieldOffset;//offset the shield slightly from the player
        }
        else
        {
            Destroy(gameObject);
        }
    }
}
