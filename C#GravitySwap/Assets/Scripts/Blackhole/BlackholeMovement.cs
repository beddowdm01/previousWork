/*A class for the movement of the blackhole*/
using UnityEngine;

public class BlackholeMovement : MonoBehaviour
{
    public static BlackholeMovement Instance;

    [SerializeField]
    private float pauseTimer = 10f;//how long to pause the blackhole
    [SerializeField]
    private float speedInc = 100f;//the speed increments a tick
    [SerializeField]
    private float speed = 0.03f;//starting speed
    [SerializeField]
    private float maxSpeed = 1.5f;

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

    void Update()
    {
        if (timer <= 0 && PauseTimer.PauseTimerActive == false)//if timer runs out
        {
            if (speed < maxSpeed)
            {
                speed += speedInc * Time.deltaTime;//increase speed
            }
            transform.Translate(speed, 0, 0);//add speed
        }
        else
        {
            timer -= Time.deltaTime;//decrement timer
        }
    }
}
