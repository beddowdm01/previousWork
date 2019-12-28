using System.Collections.Generic;
using UnityEngine;

public class BlackholeGravity : MonoBehaviour
{
    public static BlackholeGravity Instance;

    [SerializeField]
    private float force = 10f;
    [SerializeField]
    private float range = 60f;

    private Vector2 direction;
    private Vector2 forceDirection;

    private List<Rigidbody2D> gravityObjectRB = new List<Rigidbody2D>();

    private void Start()
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
        GetGravityObjectRB();
    }

    private void FixedUpdate()
    {
        foreach (Rigidbody2D rb in gravityObjectRB)
        {
            if ((rb.transform.position.x - transform.position.x) < range)
            {
                direction = ((rb.transform.position - transform.position) * force);
                forceDirection = new Vector2(((range - direction.x) * -1), direction.y);
                rb.AddForce((-forceDirection), ForceMode2D.Force);
            }
        }
    }


    public void GetGravityObjectRB()
    {
        GameObject[] gravityObjects = gravityObjects = GameObject.FindGameObjectsWithTag("GravityObjects");
        if(gravityObjects != null)
        {
            foreach (GameObject obj in gravityObjects)
            {
                gravityObjectRB.Add(obj.GetComponent<Rigidbody2D>());
            }
        }
        gravityObjectRB.Add(PlayerMovement.Instance.GetComponent<Rigidbody2D>());
    }

    public void RemoveRigidBody(Rigidbody2D rb)
    {
        gravityObjectRB.Remove(rb);
    }
}
