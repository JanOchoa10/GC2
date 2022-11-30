#ifndef _tiempo
#define _tiempo

#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <d3dx10math.h>

struct Degradado {
	float indiceSkydome;
	float valorDesvanecido;
};

class Tiempo {
private:
	int tiempoSeccionDia;
	float velocidadCambio;
	int contador;
	bool cambiandoSeccion;
	Degradado desvanecido;

public: 
	Tiempo() {

	}
	Tiempo(float indiceSkydome, int tiempoSeccionDia, float velocidadCambio) {
		this->desvanecido.indiceSkydome = indiceSkydome;
		this->tiempoSeccionDia = tiempoSeccionDia;
		this->velocidadCambio = velocidadCambio;
		this->contador = 0;
		this->desvanecido.valorDesvanecido = 0.0f;
		this->cambiandoSeccion = false;
	}
	~Tiempo() {

	}

	void definirTiempo(float indiceSkydome, int tiempoSeccionDia, float velocidadCambio) {
		this->desvanecido.indiceSkydome = indiceSkydome;
		this->tiempoSeccionDia = tiempoSeccionDia;
		this->velocidadCambio = velocidadCambio;
		this->contador = 0;
		this->desvanecido.valorDesvanecido = 0.0f;
		this->cambiandoSeccion = false;
	};

	void updateTiempo() {
		if (cambiandoSeccion == true) {
			if (desvanecido.valorDesvanecido < 1.0f) {
				desvanecido.valorDesvanecido += velocidadCambio;
			}
			else if (desvanecido.valorDesvanecido >= 1.0f) {
				desvanecido.valorDesvanecido = 0.0f;
				cambiandoSeccion = false;

				if (desvanecido.indiceSkydome < 3.0f) {
					desvanecido.indiceSkydome += 1.0f;
				}
				else
					desvanecido.indiceSkydome = 0.0f;
			}
		}
		else {
			if (contador < tiempoSeccionDia) {
				contador++;
			}
			else if(contador >= tiempoSeccionDia){
				cambiandoSeccion = true;
				contador = 0;
			}
		}
	}

	Degradado* getDesvanecido() {
		return &(desvanecido);
	}

	int getContador() {
		return contador;
	}
};
#endif
