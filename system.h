#ifndef CODE_SYSTEM_H
#define CODE_SYSTEM_H

#include <iostream>
#include <vector>
#include <zconf.h>

typedef double real;

// deltaTime изменяется в секундах
static const real deltaTime = 1 / 600.f;

// мера взаимодействия частиц
static const real K = 3.f;

struct Vector1 {
    real x;
};

struct Atom {
public:
    Atom(Vector1 position, real omegaNull, real mass) {
        this->centerPosition = this->position = position;
        this->omegaNull = omegaNull;
        this->mass = mass;
        velocity = 0;
    }

    // собственная частота, масса - кг, позиция в м
    real omegaNull;
    real mass;
    Vector1 centerPosition;
    Vector1 position;
    real velocity;

    real deltaPosition() {
        return position.x - centerPosition.x;
    }
};

struct System {
    std::vector<Atom> atoms;

    System(int N, real distance, real mass, real omegaNull) {
        for (int i = 0; i < N; i++) {
            atoms.emplace_back(Vector1{i * distance}, mass, omegaNull);
            atoms[i].position.x += 0.1;
        }

        atoms[0].position.x -= 5.f;
    }

    void simulate() {
        for (int i = 0; i < atoms.size(); i++) {
            //  расчитываю силу действующую на каждый атом
            real k = atoms[i].omegaNull * atoms[i].omegaNull * atoms[i].mass;
            real force = -k * atoms[i].deltaPosition();
            if (i != 0)
                force += K * (-(atoms[i].deltaPosition() - atoms[i - 1].deltaPosition()));
            if (i != (atoms.size() - 1))
                force += K * (-(atoms[i].deltaPosition() - atoms[i + 1].deltaPosition()));

            // расчитываю скорость для каждого атома
            real a = force / atoms[i].mass;
            atoms[i].velocity += a * deltaTime;
        }

        // расчитываю смещение каждого атома
        for (int i = 0; i < atoms.size(); i++) {
            atoms[i].position.x += atoms[i].velocity * deltaTime;
        }
    }

    void printPosition() {
        for (int i = 0; i < atoms.size(); i++) {
            std::cout << atoms[i].position.x << " ";
        }
        std::cout << std::endl;
    }
};

#endif //CODE_SYSTEM_H
