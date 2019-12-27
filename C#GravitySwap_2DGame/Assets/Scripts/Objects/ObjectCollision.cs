/*handles object collision with blackholes*/
using UnityEngine;

public class ObjectCollision : MonoBehaviour
{
    public ParticleSystem fx;

    private void OnTriggerEnter2D(Collider2D collisionInfo)
    {
        if (collisionInfo.tag == "mainBlackhole" || collisionInfo.tag == "blackhole")//if collider is a blackhole
        {
            FindObjectOfType<AudioManager>().Play("Explosion");
            Destroy(gameObject);
            ParticleSystem sparks = Instantiate(fx, transform.position, Quaternion.identity);
        }
    }
    private void OnCollisionEnter2D(Collision2D collision)//play a sound if collides with another object
    {
        FindObjectOfType<AudioManager>().Play("Collision");
    }
}
