using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    public float speed = 500.0f;
    public float maxLifetime = 10.0f;

    private Rigidbody2D rigidBody;

    // called once in the lilfetime of the script
    private void Awake()
    {
        rigidBody = GetComponent<Rigidbody2D>(); // it ll look in the same component
    }

    // we have to project in a particular direrction based on the rottion of the player - 
    // so the player determines
    public void Project(Vector2 direction)
    {
        // add force in the direction given by the player
        rigidBody.AddForce(direction * this.speed);

        Destroy(this.gameObject, this.maxLifetime);
    }

    // automatically called when our bullet collides with something
    // as we have defined rigid body and collision2d
    private void OnCollisionEnter2D(Collision2D collision)
    {
        Destroy(this.gameObject);
    }
}
