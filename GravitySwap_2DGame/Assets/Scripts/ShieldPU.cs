/*adds a shield to the player if the player collides with the shield boxcollision*/
using UnityEngine;

public class ShieldPU : MonoBehaviour
{
    private PlayerControls player;

    private void OnTriggerEnter2D(Collider2D collisionInfo)
    {
        if (collisionInfo.name == "Player")
        {
            player = FindObjectOfType<PlayerControls>();
            player.Shield();//runs the shield method in playercontrols.
            Destroy(gameObject);
        }
    }
}
