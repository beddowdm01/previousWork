/*If the player reaches the end zone of the level*/
using UnityEngine;

public class EndCollision : MonoBehaviour
{
    public GameManager gameManager;

    private void OnTriggerEnter2D(Collider2D collisionInfo)
    {
        if (collisionInfo.name == "Player")
        {
            gameManager.CompleteLevel();//runs the complete level method in the gamemanager
            Debug.Log("level complete");
        }
    }
}
