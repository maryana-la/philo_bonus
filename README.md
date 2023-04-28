# philo_processes

## C solution for Dining Philosophers problem explnation

Philosophers dine together at the same table. All the forks are put in the middle of the table, the quantity of forks equals to the number of philosophers. 

The dish served is a kind of spaghetti which has to be eaten with two forks, so philosopher can only eat when he has 2 forks. After the meal the philosopher returns forks to the middle of the table. 

The problem is to design a regimen such that no philosopher will starve, i.e., each can forever continue to alternate between eating and thinking, assuming that no philosopher can know when others may want to eat or think.

![forks_in_the_middle Small](https://user-images.githubusercontent.com/75047240/235220312-5f681c58-b697-4d6d-98f4-b3660734fe8f.jpeg)


## Usage

```bash
make
./philo 3 600 200 200 4
```

- number_of_philosophers: The number of philosophers and also the number of forks.
- time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.


## Test cases

No philosopher should die
```text
5 800 200 200
5 600 150 150
4 410 200 200
100 800 200 200
105 800 200 200
200 800 200 200
```

Philosopher should die
```text
1 800 200 200
4 310 200 100
4 200 205 200
```

Simulation should stop after indicated number of meals
```text
5 800 200 200 2
4 410 200 200 10
```

Program should not crash
```text
-5 600 200 200
4 -5 200 200
4 600 -5 200
4 600 200 -5
4 600 200 200 -5
```
