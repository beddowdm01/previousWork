/*turns off environment box collisions so that the player character can move through them freely for a period of time*/
using UnityEngine;

public class GhostPU : MonoBehaviour
{
    public float ghostTimer = 5f;//amount of time player can move through environment

    private GameObject[] walls;//array of game walls
    private SpriteRenderer[] sprites;
    private bool hit = false;

    private void OnTriggerEnter2D(Collider2D collisionInfo)
    {
        if (collisionInfo.name == "Player")
        {
            PlayerCharacter.Instance.Ghost();//runs the ghost method in player
            hit = true;
            walls =  GameObject.FindGameObjectsWithTag("Wall");

            foreach (GameObject wall in walls)
            {
                wall.GetComponent<Collider2D>().enabled = false;
            }
        }
        sprites = gameObject.GetComponentsInChildren<SpriteRenderer>();
        foreach (SpriteRenderer sprite in sprites)
        {
            Destroy(sprite);//destroys the gameobject sprite to ensure it appears like it has been destroyed
        }        
    }

    private void Update()
    {
        if (hit == true)//
        {
            ghostTimer -= Time.deltaTime;
            if (ghostTimer <= 0)//when the timer has run out
            {
                foreach (GameObject wall in walls)
                {
                    wall.GetComponent<Collider2D>().enabled = true;
                }
                PlayerCharacter.Instance.Unghost();//runs the unghost method to turn off the powerup
                Destroy(gameObject);
            }
        }
    }
}
