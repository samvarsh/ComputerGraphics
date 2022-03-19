using System.Collections;
using System.Collections.Generic;

using UnityEngine;

public class AsteroidSpawner : MonoBehaviour
{
    public Asteroid asteroidPrefab;
    public float spawnRate = 2.0f;
    public int spawnAmount = 1;
    public float spawnDistance = 15.0f; // to spawn the asteroids from outside the screen
    // spawner placed in the center. Asteroid spawned around in the edge of the circle
    // Spawner spawns around it
    public float trajectoryVariance = 15.0f;

    // To spawn asterroids at a regular rate
    private void Start()
    {
        Debug.Log(this.spawnRate);
        InvokeRepeating(nameof(Spawn), this.spawnRate, this.spawnRate); //called once every spawn rate - Spawn()
    }

    private void Spawn()
    {
        for(int i = 0; i < this.spawnAmount; i++)
        {
            Vector3 spawnDirection = Random.insideUnitCircle.normalized * this.spawnDistance;
            Vector3 spawnPoint = this.transform.position + spawnDirection;

            float variance = Random.Range(-this.trajectoryVariance, this.trajectoryVariance);
            Quaternion rotation = Quaternion.AngleAxis(variance, Vector3.forward);//vector3.forward is the z axis. variance is the rotation amount, along the z axis

            Asteroid asteroid = Instantiate(this.asteroidPrefab, spawnPoint, rotation);
            asteroid.size = Random.Range(asteroid.minSize, asteroid.maxSize);
            asteroid.SetTrajectory(rotation * -spawnDirection);
        }
    }

    public void DecreaseSpawnRate()
    {
        this.spawnRate = 0.5f;
    }

}
