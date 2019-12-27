/*If the blackhole is in range then it will cause physics movement towards it*/
using UnityEngine;

public class BlackholeSettings : MonoBehaviour
{
    public Rigidbody2D rb;
    private BlackholeMovement blackhole;

    public float force = 10f;
    public Vector2 direction;
    public Vector2 tt;
    public float range = 60;//default range variable

    private void Start()
    {
        blackhole = FindObjectOfType<BlackholeMovement>();//sets blackhole variable
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if ((transform.position.x - blackhole.transform.position.x) < range  )//if in range, add force towards blackhole
        {           
            direction = ((transform.position - blackhole.transform.position)*force);
            tt = new Vector2(((range - direction.x) * -1), direction.y);
            rb.AddForce((-tt), ForceMode2D.Force);
        }
    }
}
