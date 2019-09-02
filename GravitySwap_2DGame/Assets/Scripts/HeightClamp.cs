/*Clamps in objects to the in game floor and roof so they cannot
 fall outside game boundaries when the ghost powerup if used*/
using UnityEngine;

public class HeightClamp : MonoBehaviour
{
    public float floor;//floor and roof location variables
    public float roof;

    private Rigidbody2D rb;

    // Update is called once per frame
    private void Start()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    void Update()//if the objects go outside of game boundaries change the position and reset velocity
    {

        if (transform.position.y > roof)
        {    
            transform.position = new Vector3(transform.position.x, roof, 0);
            rb.velocity = new Vector2(rb.velocity.x,0);
        }
        if (transform.position.y < floor)
        {
            rb.velocity = new Vector2(rb.velocity.x, 0);
            transform.position = new Vector3(transform.position.x, floor, 0);
        }
    }
}
