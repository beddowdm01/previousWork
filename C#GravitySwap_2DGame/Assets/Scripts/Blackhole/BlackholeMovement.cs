/*A class for the movement of the blackhole*/
using UnityEngine;

public class BlackholeMovement : MonoBehaviour
{
    public static BlackholeMovement Instance;

    [SerializeField]
    private float pauseTimer = 10f;//how long to pause the blackhole
    [SerializeField]
    private float speedInc = 0.01f;//the speed increments a tick
    [SerializeField]
    private float speed = 0.03f;//starting speed

    private float timer;//timer used for stopping the blackhole with the slow powerup

    private void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
        }
        else
        {
            Destroy(gameObject);
            return;
        }
    }

    public void PausePowerup()
    {
        timer += pauseTimer;//increment timer
    }

    void FixedUpdate()
    {
        if (timer <= 0)//if timer runs out
        {
            speed += speedInc;//increase speed
            transform.Translate(speed, 0, 0);//add speed
        }
        else
        {
            timer -= Time.deltaTime;//decrement timer
        }
    }
}
