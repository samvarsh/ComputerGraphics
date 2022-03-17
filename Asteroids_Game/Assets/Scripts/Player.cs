using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    public float thrustSpeed = 1.0f;
    public float turnSpeed = 1.0f;
    public Bullet bulletPrefab;

    private Rigidbody2D rigidBody;
    private bool thrusting;
    private float turnDirection;

    // called once in the lilfetime of the script
    private void Awake()
    {
        rigidBody = GetComponent<Rigidbody2D>(); // it ll look in the same component
    }

    // Update is called once per frame - for every single frame our game is running
    private void Update()
    {
        thrusting = Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.UpArrow);

        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow))
            turnDirection = 1.0f;
        else if (Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow))
            turnDirection = -1.0f;
        else
            turnDirection = 0.0f;

        if (Input.GetKeyDown(KeyCode.Space))
            Shoot();

    }

    private void FixedUpdate()
    {
        // called on a fixed time interval- physics updates
        // Rigid body things

        if (thrusting)
            rigidBody.AddForce(this.transform.up * this.thrustSpeed);

        if(turnDirection != 0.0f)
            rigidBody.AddTorque(turnDirection * this.turnSpeed);
    }

    private void Shoot()
    {
        // each time the player shoots we instantiate a new bullet 
        Bullet bullet = Instantiate(this.bulletPrefab, this.transform.position, this.transform.rotation);
        bullet.Project(this.transform.up);
    }
}
