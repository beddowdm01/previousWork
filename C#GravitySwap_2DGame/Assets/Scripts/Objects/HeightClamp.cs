/*Clamps in objects to the in game floor and roof so they cannot
 fall outside game boundaries when the ghost powerup if used*/
using UnityEngine;

public class HeightClamp : MonoBehaviour
{
    [SerializeField]
    private float floorHeight = -10f;//floor and roof location variables
    [SerializeField]
    private float roofHeight = 10f;

    private Rigidbody2D rb;

    // Update is called once per frame
    private void Start()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    void Update()//if the objects go outside of game boundaries change the position and reset velocity
    {

        if (transform.position.y > roofHeight)
        {    
            transform.position = new Vector3(transform.position.x, roofHeight, 0);
            rb.velocity = new Vector2(rb.velocity.x,0);
        }
        if (transform.position.y < floorHeight)
        {
            rb.velocity = new Vector2(rb.velocity.x, 0);
            transform.position = new Vector3(transform.position.x, floorHeight, 0);
        }
    }
}
