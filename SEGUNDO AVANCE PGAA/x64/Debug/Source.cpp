#include <Windows.h>
#include "resource.h"
#include <CommDlg.h>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;


//Administrador
struct admin {
	admin* ant;
	char nombre[50] = { 0 };
	char pass[50] = { 0 };
	char foto[MAX_PATH] = { 0 };
	char nombreCompleto[50] = { 0 };
	char alias[50] = { 0 };
	char comercio[50] = { 0 };
	admin* sig;
};
admin* miInfo, * aux, * aux2, * inicio = nullptr;

//Contador 
struct contador {
	contador* Cant;
	char Cnombre[50] = { 0 };
	char Cpass[50] = { 0 };
	char Cfoto[MAX_PATH] = { 0 };
	char CnombreCompleto[50] = { 0 };
	char Calias[50] = { 0 };
	char Ccomercio[50] = { 0 };
	contador* Csig;
};
contador* CmiInfo, * Caux, * Caux2, * Cinicio = nullptr;


//Cliente 
struct cliente {
	cliente* Clant;
	char Clnombre[50] = { 0 };
	char Clalias[50] = { 0 };
	char telefono[50] = { 0 };
	char correo[50] = { 0 };
	char fecha[10] = { 0 };
	char Clcomercio[50] = { 0 };
	int nunero = 0;
	int numero = 0;
	cliente* Clsig;
};
cliente* ClmiInfo, * Claux, * Claux2, * Clinicio = nullptr;

struct promociones {
	promociones* proant;
	char pronombre[50] = { 0 };
	int pmonto = 0;
	float porcentajedes = 0;
	int estatus = 0;
	char Clcomercio[50] = { 0 };
	promociones* prosig;
};
promociones* promiinfo, * proaux, * proaux2, * proinicio = nullptr;

struct compras {
	compras* coant;
	char cliente[50] = { 0 };
	int monto;
	float subtotal;
	float descuento;
	float total;
	char Comcomercio[50] = { 0 };
	char fecha[50] = { 0 };
	char fechaexacta[50] = { 0 };
	char fechaultima[50] = { 0 };
	int comrpastotal = 0;
	compras* cosig;
};
compras* comiinfo, * coaux, * coaux2, * comincio = nullptr;

int* Monto;
char cli[50] = { 0 };
char* clientes;

//Puntero VP
int* Opc;
int* montoTotal;
int* proactive;
int* proinactive;
int* numcl;
int* numCl;
int* consutotal;
float* totalcompras;

LRESULT CALLBACK procVIS(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK procVR(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK procVPI(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK procVP(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK procAltaUsu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK procResetPassUsu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK procListUsu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK procModifiyListU(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK procAltaCli(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK procListaCli(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK procAltaPro(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK procListaPro(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK procAltaConsu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK procListaConsu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


//FUNCIONES
void validacion(admin* temp1);
void validacionC(contador* temp2);
void validacioncliente(cliente* temp3);

//ADMINISTRADOR 
void agregaradmin(admin* temp1);
void agregaradmin2(admin* temp1);
void modificar(admin* newInfo, char nomUsuario[50]);
void eliminar(char nomUsu[50]);
void escribirUsuario();
void leerUsuario();

//Cajero
void agregarcajero(contador* temp2);
void modificarC(contador* newInfo, char nomUsuario[50]);
void eliminarC(char nomUsu[50]);
void escribircajero();
void leercajero();

//Cliente 
void agregarcliente(cliente* temp3);
void modificarCl(cliente* newInfo, char nomUsuario[50]);
void eliminarCl(char nomUsu[50]);
void ecribircliente();
void leercliente();

//Promocoiones 
void agregarpromo(promociones* temp4);
void modificarpromocion(promociones* newInfo, char pronombre[50]);
void eliminarpromo(char pronombre[50]);
void ventanapromo(promociones* acic);
void escribirpromo();
void leerpromo();

//Consumos
void agregarconsumos(compras* temp5);
void modificartotalconsumo(char cliente[50], int montototal = 0);
void eliminarconsumos(char nomcomsumo[50]);
void ventanaconsumo(compras* acic);
void escribirconsumos();
void leerconsumos();

HINSTANCE hInstGlobal;
HANDLE hBitmap;
HWND hPrinGlob;
char zFile[MAX_PATH]; //256 caracteres

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
	hInstGlobal = hInst;
	leerUsuario();
	leercajero();
	leercliente();
	leerpromo();
	leerconsumos();

	HWND hVIS = CreateDialog(hInst, MAKEINTRESOURCE(ID_DIAIS), NULL, procVIS);

	ShowWindow(hVIS, cmdshow);

	MSG mensajes;

	while (GetMessage(&mensajes, 0, 0, 0)) {
		TranslateMessage(&mensajes);
		DispatchMessage(&mensajes);
	}
	escribirUsuario();
	escribircajero();
	ecribircliente();
	ecribircliente();
	escribirconsumos();
	return mensajes.wParam;
}

LRESULT CALLBACK procVIS(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_INITDIALOG:
	{
		char comercios[50] = { 0 };

		aux = inicio;
		Caux = Cinicio;

		if (aux != nullptr)
		{
			while (aux != nullptr) {

				SendDlgItemMessage(hwnd, ID_COMBO_COIS, CB_INSERTSTRING, 0, (LPARAM)aux->comercio);
				aux = aux->sig;
			}
			if (Caux != nullptr)
			{
				while (Caux != nullptr) {

					SendDlgItemMessage(hwnd, ID_COMBO_COIS, CB_INSERTSTRING, 0, (LPARAM)Caux->Ccomercio);
					Caux = Caux->Csig;

				}
			}
		}


	}break;
	case WM_COMMAND: {
		if (LOWORD(wParam) == ID_BUTTExitIS)
		{
			int opc = 0;
			opc = MessageBox(hwnd, "�Est� seguro que quiere salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
			if (opc == 6) {
				DestroyWindow(hwnd);
				PostQuitMessage(0);

			}
		}
		if (LOWORD(wParam) == ID_BUTTRegisIS) {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAREGIS), hwnd, procVR);

		}
		if (LOWORD(wParam) == ID_BUTTEnterIS) {
			char nomIni[50] = { 0 };
			char passIni[50] = { 0 };
			char comercio[50] = { 0 };
			GetDlgItemText(hwnd, ID_EDITNomUsuIS, nomIni, sizeof(nomIni));
			GetDlgItemText(hwnd, ID_ConIS, passIni, sizeof(passIni));


			aux = inicio;
			Caux = Cinicio;

			SendDlgItemMessage(hwnd, ID_COMBO_COIS, WM_GETTEXT, 50, (LPARAM)comercio);

			if (aux == inicio) {
				if (aux == nullptr) {
					if (Caux == nullptr) {

						MessageBox(hwnd, "No hay usuarios registrados", "AVISO", MB_OK | MB_ICONERROR);

					}
					else {
						while (Caux != nullptr && strcmp(nomIni, Caux->Cnombre) != 0) {
							Caux = Caux->Csig;
						}
						if (Caux == nullptr) {
							MessageBox(hwnd, "El usuario no est� registrado", "AVISO", MB_OK | MB_ICONERROR);
						}
						else {
							if (strcmp(comercio, Caux->Ccomercio) == 0)
							{
								if (strcmp(passIni, Caux->Cpass) == 0) {
									CmiInfo = Caux;
									EndDialog(hwnd, 0);
									char vacio[1] = { "" };
									if (strcmp(CmiInfo->CnombreCompleto, CmiInfo->Cfoto) == 0)
									{
										DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_IU_VP), NULL, procVPI);

									}
									else {
										int a = -858993460;
										Opc = &a;

										DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), NULL, procVP);
									}
								}
								else {
									MessageBox(hwnd, "Contrase�a incorrecta", "AVISO", MB_OK | MB_ICONERROR);
								}
							}
							else {
								MessageBox(hwnd, "Usuario  inexistente", "AVISO", MB_OK | MB_ICONERROR);
							}

						}
					}
					MessageBox(hwnd, "No hay usuarios registrados", "AVISO", MB_OK | MB_ICONERROR);
				}
				else {

					if (Caux != nullptr) {
						while (Caux != nullptr && strcmp(nomIni, Caux->Cnombre) != 0) {
							Caux = Caux->Csig;
						}
						if (Caux == nullptr)
						{

							while (aux != nullptr && strcmp(nomIni, aux->nombre) != 0) {
								aux = aux->sig;
							}
							if (aux == nullptr)
							{
								MessageBox(hwnd, "El usuario no est� registrado", "AVISO", MB_OK | MB_ICONERROR);

							}
							else if (strcmp(nomIni, aux->nombre) == 0) {
								if (strcmp(comercio, aux->comercio) == 0) {

									if (strcmp(passIni, aux->pass) == 0) {
										miInfo = aux;
										EndDialog(hwnd, 0);
										char vacio[1] = { "" };
										if (strcmp(miInfo->nombreCompleto, miInfo->foto) == 0)
										{

											DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_IU_VP), NULL, procVPI);

										}
										else {
											int a = -858993460;
											Opc = &a;

											DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), NULL, procVP);
										}
									}
									else {
										MessageBox(hwnd, "Contrase�a incorrecta", "AVISO", MB_OK | MB_ICONERROR);
									}

								}
								else
								{
									MessageBox(hwnd, "Usuario  inexistente", "AVISO", MB_OK | MB_ICONERROR);

								}
							}

						}
						else if (strcmp(Caux->Cnombre, nomIni) == 0)
						{
							if (strcmp(comercio, Caux->Ccomercio) == 0)
							{
								if (strcmp(passIni, Caux->Cpass) == 0) {
									CmiInfo = Caux;
									EndDialog(hwnd, 0);
									char vacio[1] = { "" };
									if (strcmp(CmiInfo->CnombreCompleto, CmiInfo->Cfoto) == 0)
									{
										DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_IU_VP), NULL, procVPI);

									}
									else {
										int a = -858993460;
										Opc = &a;

										DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), NULL, procVP);
									}
								}
								else
								{
									while (aux != nullptr && strcmp(nomIni, aux->nombre) != 0) {
										aux = aux->sig;
									}
									if (aux == nullptr)
									{
										MessageBox(hwnd, "El usuario no est� registrado", "AVISO", MB_OK | MB_ICONERROR);

									}
									else if (strcmp(nomIni, aux->nombre) == 0) {
										if (strcmp(comercio, aux->comercio) == 0) {

											if (strcmp(passIni, aux->pass) == 0) {
												miInfo = aux;
												EndDialog(hwnd, 0);
												char vacio[1] = { "" };
												if (strcmp(miInfo->nombreCompleto, miInfo->foto) == 0)
												{

													DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_IU_VP), NULL, procVPI);

												}
												else {
													int a = -858993460;
													Opc = &a;

													DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), NULL, procVP);
												}
											}
											else {
												MessageBox(hwnd, "Contrase�a incorrecta", "AVISO", MB_OK | MB_ICONERROR);
											}

										}
									}

								}
							}
							else {
								MessageBox(hwnd, "Usuario  inexistente", "AVISO", MB_OK | MB_ICONERROR);
							}

						}
					}

					else {
						while (aux != nullptr && strcmp(nomIni, aux->nombre) != 0) {
							aux = aux->sig;
						}
						if (aux == nullptr) {

						}
						else if (strcmp(nomIni, aux->nombre) == 0) {
							if (strcmp(comercio, aux->comercio) == 0) {

								if (strcmp(passIni, aux->pass) == 0) {
									miInfo = aux;
									EndDialog(hwnd, 0);
									char vacio[1] = { "" };
									if (strcmp(miInfo->nombreCompleto, miInfo->foto) == 0)
									{

										DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_IU_VP), NULL, procVPI);

									}
									else {
										int a = -858993460;
										Opc = &a;

										DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), NULL, procVP);
									}
								}
								else {
									MessageBox(hwnd, "Contrase�a incorrecta", "AVISO", MB_OK | MB_ICONERROR);
								}

							}
						}

					}

				}
			}

		}

	}break;
	}
	return false;
}

LRESULT CALLBACK procVR(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_INITDIALOG: {


	case ID_RAD_ADMINREGIS: {
		SendDlgItemMessage(hwnd, ID_RAD_ADMINREGIS, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
	}break;

	case ID_RAD_CAJREGIS: {
		SendDlgItemMessage(hwnd, ID_RAD_CAJREGIS, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);

	}break;

	}break;

	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case ID_BUTTRetREGIS: {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAIS), hwnd, procVIS);
		}break;

		case ID_RAD_ADMINREGIS: {

		}break;
		case ID_RAD_CAJREGIS: {


		}break;
		case ID_BUTTEnterREGIS: {

			char vacio[1] = { "" };
			admin* temp1 = new admin;

			GetDlgItemText(hwnd, ID_EDITNoUsREGIS, temp1->nombre, 50);
			GetDlgItemText(hwnd, ID_EDITConREGIS, temp1->pass, 50);
			GetDlgItemText(hwnd, ID_EDITComREGIS, temp1->comercio, 50);
			int charnombre;
			int charespnombre = 0, numnombre = 0, letrasnombre;
			charnombre = strlen(temp1->nombre);

			char equisde[15];
			GetDlgItemText(hwnd, ID_EDITNoUsREGIS, equisde, sizeof(equisde));
			aux = inicio;
			if (charnombre == 0) {
				MessageBox(hwnd, "Ingrese un nombre", "AVISO", MB_OK | MB_ICONERROR);
			}
			else {
				if (charnombre > 15) {
					MessageBox(hwnd, "Su nombre de usuario es muy largo", "AVISO", MB_OK | MB_ICONERROR);
				}
				else {
					for (int i = 0; i < charnombre; i++) {
						if (ispunct(temp1->nombre[i])) {
							charespnombre++;

						}
						if (isdigit(temp1->nombre[i])) {
							numnombre++;
						}
					}
					if (charespnombre != 0 || numnombre != 0) {
						MessageBox(hwnd, "Su nombre no puede contener caracteres no alfanumericos", "AVISO", MB_OK | MB_ICONERROR);
					}
					else {
						charespnombre = 0;
						numnombre = 0;

						while (aux != nullptr && strcmp(aux->nombre, equisde) != 0) {
							aux = aux->sig;
						}
						if (aux != nullptr) {
							MessageBox(hwnd, "Usuario ya existente, ingrese uno valido", "AVISO", MB_OK | MB_ICONERROR);
						}
						else {
							charespnombre = 0;
							numnombre = 0;
							letrasnombre = 0;
							charnombre = strlen(temp1->pass);
							if (charnombre == 0) {
								MessageBox(hwnd, "Ingrese una contrase�a", "AVISO", MB_OK | MB_ICONERROR);
							}
							else {
								if (charnombre < 3 || charnombre > 10) {
									MessageBox(hwnd, "La contrase�a debe incluir una letra, un n�mero y un caracter especial.", "AVISO", MB_OK | MB_ICONERROR);
								}
								else {
									for (int i = 0; i < charnombre; i++) {
										if (ispunct(temp1->pass[i])) {
											charespnombre++;
										}
										if (isdigit(temp1->pass[i])) {
											numnombre++;
										}
										if (isalpha(temp1->pass[i])) {
											letrasnombre++;
										}
									}
									if (charespnombre == 0 && numnombre == 0 && letrasnombre == 0) {
										MessageBox(hwnd, "Contrase�a no valida", "AVISO", MB_OK | MB_ICONERROR);
									}
									else {
										charespnombre = 0;
										numnombre = 0;
										letrasnombre = 0;
										charnombre = strlen(temp1->comercio);
										char equisde[15];
										GetDlgItemText(hwnd, ID_EDITComREGIS, equisde, sizeof(equisde));
										if (charnombre == 0) {
											MessageBox(hwnd, "Ingrese un comercio", "AVISO", MB_OK | MB_ICONERROR);
										}
										else {
											aux = inicio;
											if (charnombre < 5 || charnombre > 15) {
												MessageBox(hwnd, "El comercio debe tener entre 5 y 15 caracteres", "AVISO", MB_OK | MB_ICONERROR);
											}
											else {
												for (int i = 0; i < charnombre; i++) {
													if (ispunct(temp1->comercio[i])) {
														charespnombre++;
													}
													if (isdigit(temp1->comercio[i])) {
														numnombre++;
													}
												}
												if (charespnombre != 0 || numnombre != 0) {
													MessageBox(hwnd, "El comercio no puede contener caracteres no alfanumericos", "AVISO", MB_OK | MB_ICONERROR);
												}
												else {
													strcpy_s(temp1->alias, "");
													strcpy_s(temp1->nombreCompleto, "");
													strcpy_s(temp1->foto, "");

													if (strcmp(temp1->nombre, vacio) == 0 && strcmp(temp1->pass, vacio) == 0 && strcmp(temp1->comercio, vacio) == 0)
													{
														MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
													}
													else {

														aux = inicio;

														if (inicio == nullptr) {
															agregaradmin(temp1);
															SetDlgItemText(hwnd, ID_EDITNoUsREGIS, "");
															SetDlgItemText(hwnd, ID_EDITConREGIS, "");
															SetDlgItemText(hwnd, ID_EDITComREGIS, "");
															miInfo = inicio;

															delete temp1;
															MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
														}
														else {
															//posible fallo 
															while (aux->sig != nullptr && strcmp(temp1->nombre, aux->nombre) != 0) {
																aux = aux->sig;
															}
															if (aux->sig == nullptr) {
																agregaradmin2(temp1);
																SetDlgItemText(hwnd, ID_EDITNoUsREGIS, "");
																SetDlgItemText(hwnd, ID_EDITConREGIS, "");
																SetDlgItemText(hwnd, ID_EDITComREGIS, "");
																miInfo = inicio;

																delete temp1;
																MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
															}
															else {
																if (strcmp(temp1->comercio, aux->comercio) == 0) {

																	if (strcmp(temp1->pass, aux->pass) == 0) {
																		MessageBox(hwnd, "Usuario ya existente", "AVISO", MB_OK || MB_ICONEXCLAMATION);

																	}
																	else {
																		agregaradmin(temp1);
																		SetDlgItemText(hwnd, ID_EDITNoUsREGIS, "");
																		SetDlgItemText(hwnd, ID_EDITConREGIS, "");
																		SetDlgItemText(hwnd, ID_EDITComREGIS, "");
																		miInfo = inicio;
																		delete temp1;
																		MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
																	}

																}
																else
																{
																	agregaradmin(temp1);
																	SetDlgItemText(hwnd, ID_EDITNoUsREGIS, "");
																	SetDlgItemText(hwnd, ID_EDITConREGIS, "");
																	SetDlgItemText(hwnd, ID_EDITComREGIS, "");
																	miInfo = inicio;
																	delete temp1;
																	MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
																}

															}

														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}

		}break;
		}
	}
	}
	return false;
}

LRESULT CALLBACK procVPI(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG: {


		char vacio[1] = { "" };
		if (miInfo != nullptr) {
			if (strcmp(miInfo->foto, miInfo->nombreCompleto) == 0)
			{
				EnableWindow(GetDlgItem(hwnd, ID_BUTTMOD_IU), false);

			}
			else
			{
				SetDlgItemText(hwnd, ID_EDITNomComIU, miInfo->nombreCompleto);
				SetDlgItemText(hwnd, ID_EDITAliUsuIU, miInfo->alias);
				EnableWindow(GetDlgItem(hwnd, ID_BUTTMOD_IU), true);
				EnableWindow(GetDlgItem(hwnd, ID_EDITNomComIU), false);
				EnableWindow(GetDlgItem(hwnd, ID_EDITAliUsuIU), false);
				EnableWindow(GetDlgItem(hwnd, ID_BUTTFotoIU), false);
				HBITMAP bmp; //1
				bmp = (HBITMAP)LoadImage(NULL, miInfo->foto, IMAGE_BITMAP, 130, 150, LR_LOADFROMFILE); //2
				SendDlgItemMessage(hwnd, ID_STAPICIDU, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 


			}

		}
		else if (CmiInfo != nullptr) {
			if (strcmp(CmiInfo->Cfoto, CmiInfo->CnombreCompleto) == 0)
			{
				EnableWindow(GetDlgItem(hwnd, ID_BUTTMOD_IU), false);

			}
			else
			{
				SetDlgItemText(hwnd, ID_EDITNomComIU, CmiInfo->CnombreCompleto);
				SetDlgItemText(hwnd, ID_EDITAliUsuIU, CmiInfo->Calias);
				EnableWindow(GetDlgItem(hwnd, ID_BUTTMOD_IU), true);
				EnableWindow(GetDlgItem(hwnd, ID_EDITNomComIU), false);
				EnableWindow(GetDlgItem(hwnd, ID_EDITAliUsuIU), false);
				EnableWindow(GetDlgItem(hwnd, ID_BUTTFotoIU), false);
				HBITMAP bmp; //1
				bmp = (HBITMAP)LoadImage(NULL, CmiInfo->Cfoto, IMAGE_BITMAP, 130, 150, LR_LOADFROMFILE); //2
				SendDlgItemMessage(hwnd, ID_STAPICIDU, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 


			}
		}

	}break;

	case WM_COMMAND: {

		switch (LOWORD(wParam)) {

		case ID_BUTTSaveIU: {
			if (miInfo != nullptr) {
				admin* temp2 = new admin;
				char vacio[1] = { "" };

				if (strcmp(miInfo->nombreCompleto, "") == 0) {

					GetDlgItemText(hwnd, ID_EDITNomComIU, temp2->nombreCompleto, sizeof(temp2->nombreCompleto));
					GetDlgItemText(hwnd, ID_EDITAliUsuIU, temp2->alias, sizeof(temp2->alias));
					GetDlgItemText(hwnd, ID_EDITAliUsuIU, temp2->foto, sizeof(temp2->foto));
					if (strcmp(temp2->nombreCompleto, vacio) == 0 && strcmp(temp2->nombreCompleto, vacio) == 0)
					{
						MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
					}
					else {

						strcpy_s(miInfo->nombreCompleto, temp2->nombreCompleto);
						strcpy_s(miInfo->alias, temp2->alias);
						strcpy_s(miInfo->foto, zFile);
						EnableWindow(GetDlgItem(hwnd, ID_BUTTMOD_IU), true);
						EnableWindow(GetDlgItem(hwnd, ID_EDITNomComIU), false);
						EnableWindow(GetDlgItem(hwnd, ID_EDITAliUsuIU), false);
						EnableWindow(GetDlgItem(hwnd, ID_BUTTFotoIU), false);
						int a = -858993460;
						Opc = &a;
						EndDialog(hwnd, 0);
						DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), NULL, procVP);


					}
				}
				else {
					char nombrecompleto[50];
					char nomalias[50];
					char foto[MAX_PATH];

					GetDlgItemText(hwnd, ID_EDITNomComIU, nombrecompleto, sizeof(nombrecompleto));
					GetDlgItemText(hwnd, ID_EDITAliUsuIU, nomalias, sizeof(nomalias));
					GetDlgItemText(hwnd, ID_STAPICIDU, foto, sizeof(foto));
					if (strcmp(nombrecompleto, vacio) == 0 && strcmp(foto, vacio) == 0)
					{
						MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
					}

					else {
						strcpy_s(miInfo->nombreCompleto, nombrecompleto);
						strcpy_s(miInfo->alias, foto);
						strcpy_s(miInfo->foto, zFile);
						EnableWindow(GetDlgItem(hwnd, ID_BUTTMOD_IU), true);
						EnableWindow(GetDlgItem(hwnd, ID_EDITNomComIU), false);
						EnableWindow(GetDlgItem(hwnd, ID_EDITAliUsuIU), false);
						EnableWindow(GetDlgItem(hwnd, ID_BUTTFotoIU), false);
					}
				}
			}
			else if (CmiInfo != nullptr) {
				contador* temp2 = new contador;
				char vacio[1] = { "" };

				if (strcmp(CmiInfo->CnombreCompleto, "") == 0) {
					GetDlgItemText(hwnd, ID_EDITNomComIU, temp2->CnombreCompleto, sizeof(temp2->CnombreCompleto));
					GetDlgItemText(hwnd, ID_EDITAliUsuIU, temp2->Calias, sizeof(temp2->Calias));
					GetDlgItemText(hwnd, ID_EDITAliUsuIU, temp2->Cfoto, sizeof(temp2->Cfoto));
					if (strcmp(temp2->CnombreCompleto, vacio) == 0 && strcmp(temp2->Cfoto, vacio) == 0)
					{
						MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
					}
					else {

						strcpy_s(CmiInfo->CnombreCompleto, temp2->CnombreCompleto);
						strcpy_s(CmiInfo->Calias, temp2->Calias);
						strcpy_s(CmiInfo->Cfoto, zFile);
						EnableWindow(GetDlgItem(hwnd, ID_BUTTMOD_IU), true);
						EnableWindow(GetDlgItem(hwnd, ID_EDITNomComIU), false);
						EnableWindow(GetDlgItem(hwnd, ID_EDITAliUsuIU), false);
						EnableWindow(GetDlgItem(hwnd, ID_BUTTFotoIU), false);
						int a = -858993460;
						Opc = &a;
						DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), NULL, procVP);



					}
				}
				else {
					char nombrecompleto[50];
					char nomalias[50];
					char foto[MAX_PATH];

					GetDlgItemText(hwnd, ID_EDITNomComIU, nombrecompleto, sizeof(nombrecompleto));
					GetDlgItemText(hwnd, ID_EDITAliUsuIU, nomalias, sizeof(nomalias));
					GetDlgItemText(hwnd, ID_STAPICIDU, foto, sizeof(foto));
					if (strcmp(nombrecompleto, vacio) == 0 && strcmp(foto, vacio) == 0)
					{
						MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
					}

					else {
						strcpy_s(CmiInfo->CnombreCompleto, temp2->CnombreCompleto);
						strcpy_s(CmiInfo->Calias, temp2->Calias);
						strcpy_s(CmiInfo->Cfoto, zFile);
						EnableWindow(GetDlgItem(hwnd, ID_BUTTMOD_IU), true);
						EnableWindow(GetDlgItem(hwnd, ID_EDITNomComIU), false);
						EnableWindow(GetDlgItem(hwnd, ID_EDITAliUsuIU), false);
						EnableWindow(GetDlgItem(hwnd, ID_BUTTFotoIU), false);
					}
				}
			}

		}break;
		case ID_BUTTFotoIU: {

			OPENFILENAME ofn;

			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "ALL\0 * .*\0Bitmaps\0 * .bmp\0";
			ofn.lpstrFile = zFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(zFile);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.nFilterIndex = 2;

			if (GetOpenFileName(&ofn) == TRUE) {
				HBITMAP bmp; //1

				bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 130, 150, LR_LOADFROMFILE); //2

				SendDlgItemMessage(hwnd, ID_STAPICIDU, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 

			}
			else {
				//Si el usuario no seleccion� una imagen, qu� se debe de hacer?
			}
		}break;
		case ID_BUTTMOD_IU: { //modificar 
			int opc = 0;
			opc = MessageBox(hwnd, "Quiere modificar?", "AVISO", MB_YESNO || MB_ICONQUESTION);
			Opc = &opc;

			if (opc == 1) {
				EnableWindow(GetDlgItem(hwnd, ID_EDITNomComIU), true);
				EnableWindow(GetDlgItem(hwnd, ID_EDITAliUsuIU), true);
				EnableWindow(GetDlgItem(hwnd, ID_BUTTFotoIU), true);

			}
		}break;
		case ID_BUTTRegINFOUSU: {
			//MSG mensaje; 
			//opc = GetMessage(&mensaje, hwnd, ID_BUTTRegINFOUSU, (LPARAM)opc);
			if (Opc == nullptr) {
				EndDialog(hwnd, 0);
				DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAIS), NULL, procVIS);

			}
			else if (*Opc == -858993460) {
				EndDialog(hwnd, 0);
				DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), NULL, procVP);

			}


		}break;
		}


	}break;
	}
	return false;
}
LRESULT CALLBACK procVP(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	hPrinGlob = hwnd;

	switch (msg) {
	case WM_INITDIALOG: {

		if (miInfo != nullptr)
		{


			proaux = proinicio;
			Claux = Clinicio;
			//char newNom[50];

			if (proaux == nullptr)
			{

				SetDlgItemText(hwnd, ID_STA_DB_PA, "No hay promociones registradas");
				SetDlgItemText(hwnd, ID_STA_DB_PI, "No hay promociones registradas");
				if (coaux == nullptr)
				{
					SetDlgItemText(hwnd, ID_STA_DB_TOCONSU, "No hay consumos realizados");
					SetDlgItemText(hwnd, ID_STA_DB_TOCOM, "No hay consumos realizados");
					if (Claux == nullptr)
					{
						SetDlgItemText(hwnd, ID_STA_DB_CLIENTES, "No hay clientes registrados");

					}
					else {

						int j = 0;

						while (Claux != nullptr)
						{
							j = Claux->numero + j;
							Claux = Claux->Clsig;
						}
						SetDlgItemInt(hwnd, ID_STA_DB_CLIENTES, (UINT)j, false);

					}
				}
				else {
					int c = 0;
					float d = 0;
					while (coaux != nullptr) {
						if (strcmp(miInfo->comercio, coaux->Comcomercio) == 0) {

							c = c + 1;

							if (coaux->total != 0) {

								d = coaux->total + d;
								totalcompras = &d;
							}
						}
						coaux = coaux->cosig;
					}
					consutotal = &c;
					SetDlgItemInt(hwnd, ID_STA_DB_TOCONSU, (UINT)c, false);
					SetDlgItemInt(hwnd, ID_STA_DB_TOCOM, (UINT)d, false);
				}
			}
			else {
				int a = 0;
				int b = 0;
				while (proaux != nullptr) {
					if (strcmp(miInfo->comercio, proaux->Clcomercio) == 0) {
						if (proaux->estatus == 0) {

							proactive = &a;
							a = a + 1;
						}
						else if (proaux->estatus == 1) {

							b = b + 1;
							proinactive = &b;
						}

					}
					proaux = proaux->prosig;
				}
				SetDlgItemInt(hwnd, ID_STA_DB_PA, (UINT)a, false);
				SetDlgItemInt(hwnd, ID_STA_DB_PI, (UINT)b, false);

				int c = 0;
				float d = 0;
				coaux = comincio;
				//char newNom[50];

				if (coaux == nullptr)
				{

					SetDlgItemText(hwnd, ID_STA_DB_TOCONSU, "No hay consumos realizados");
					SetDlgItemText(hwnd, ID_STA_DB_TOCOM, "No hay consumos realizados");
				}
				else {
					while (coaux != nullptr) {
						if (strcmp(miInfo->comercio, coaux->Comcomercio) == 0) {

							c = c + 1;

							if (coaux->total != 0) {

								d = coaux->total + d;
							}
						}
						coaux = coaux->cosig;
					}
					consutotal = &c;
					SetDlgItemInt(hwnd, ID_STA_DB_TOCONSU, (UINT)c, false);
					SetDlgItemInt(hwnd, ID_STA_DB_TOCOM, (UINT)d, false);
				}

			}

		}

		else if (CmiInfo != nullptr) {
			if (proaux == nullptr)
			{

				SetDlgItemText(hwnd, ID_STA_DB_PA, "No hay promociones registradas");
				SetDlgItemText(hwnd, ID_STA_DB_PI, "No hay promociones registradas");

				if (coaux == nullptr)
				{

					SetDlgItemText(hwnd, ID_STA_DB_TOCONSU, "No hay consumos realizados");
					SetDlgItemText(hwnd, ID_STA_DB_TOCOM, "No hay consumos realizados");
					if (Claux == nullptr)
					{
						SetDlgItemText(hwnd, ID_STA_DB_CLIENTES, "No hay clientes registrados");

					}
					else {
						int j = 0;

						while (Claux != nullptr)
						{

							j = Claux->numero + j;
							Claux = Claux->Clsig;

						}
						SetDlgItemInt(hwnd, ID_STA_DB_CLIENTES, (UINT)j, false);
					}

				}
				else if (CmiInfo != nullptr) {
					int c = 0;
					float d = 0;
					while (coaux != nullptr) {
						if (strcmp(CmiInfo->Ccomercio, coaux->Comcomercio) == 0) {

							c = c + 1;

							if (coaux->total != 0) {

								d = coaux->total + d;
								totalcompras = &d;
							}
						}
						coaux = coaux->cosig;
					}
					consutotal = &c;
					SetDlgItemInt(hwnd, ID_STA_DB_TOCONSU, (UINT)c, false);
					SetDlgItemInt(hwnd, ID_STA_DB_TOCOM, (UINT)d, false);
				}
			}
			else {
				int a = 0;
				int b = 0;
				while (proaux != nullptr) {
					if (strcmp(CmiInfo->Ccomercio, proaux->Clcomercio) == 0) {
						if (proaux->estatus == 0) {

							proactive = &a;
							a = a + 1;
						}
						else if (proaux->estatus == 1) {

							b = b + 1;
							proinactive = &b;
						}

					}
					proaux = proaux->prosig;
				}
				SetDlgItemInt(hwnd, ID_STA_DB_PA, (UINT)a, false);
				SetDlgItemInt(hwnd, ID_STA_DB_PI, (UINT)b, false);
				int c = 0;
				float d = 0;
				coaux = comincio;
				//char newNom[50];

				if (coaux == nullptr)
				{

					SetDlgItemText(hwnd, ID_STA_DB_TOCONSU, "No hay consumos realizados");
					SetDlgItemText(hwnd, ID_STA_DB_TOCOM, "No hay consumos realizados");
				}
				else if (CmiInfo != nullptr) {
					while (coaux != nullptr) {
						if (strcmp(CmiInfo->Ccomercio, coaux->Comcomercio) == 0) {

							c = c + 1;

							if (coaux->total != 0) {

								d = coaux->total + d;
								totalcompras = &d;
							}
						}
						coaux = coaux->cosig;
					}
					consutotal = &c;
					SetDlgItemInt(hwnd, ID_STA_DB_TOCONSU, (UINT)c, false);
					SetDlgItemInt(hwnd, ID_STA_DB_TOCOM, (UINT)d, false);
				}

			}
		}




	}break;

	case WM_COMMAND: {
		switch (LOWORD(wParam)) {

		case  ID_INFORMACION_IU_VP: {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_IU_VP), hwnd, procVPI);
		}break;

		case ID_ALTA_USU_VP: {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGALTAUSU_VP), hwnd, procAltaUsu);
		}break;

		case ID_RESETPASS_USU_VP: {
			aux = inicio;
			Caux = Cinicio;
			if (aux != nullptr || Caux != nullptr)
			{
				EndDialog(hwnd, 0);
				DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGRESETCON_U_VP), hwnd, procResetPassUsu);

			}
			else
			{
				MessageBox(hwnd, "No hay usuarios ingresados", "AVISO", MB_YESNO | MB_ICONQUESTION);
			}
		}break;

		case ID_LISTUSU_USU_VP: {
			if (aux != nullptr || Caux != nullptr)
			{
				EndDialog(hwnd, 0);
				DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGLISTU_U_VP), hwnd, procListUsu);

			}
			else
			{
				MessageBox(hwnd, "No hay usuarios ingresados", "AVISO", MB_YESNO | MB_ICONQUESTION);
			}
		}break;

		case ID_REGISCUSTO_CUSTO_VP: {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGALTACLI_CLI_VP), hwnd, procAltaCli);
		}break;

		case ID_LISTCUSTO_CUSTOS_VP: {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGLISTCLI_CLI_VP), hwnd, procListaCli);
		}break;

		case ID_REGSPROM_PROM_VP: {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGALTAPRO_PRO_VP), hwnd, procAltaPro);
		}break;

		case ID_LISTPROM_PROM_VP: {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGLISTPRO_PRO_VP), hwnd, procListaPro);
		}break;
		case ID_REGSCOMP_COMP_VP: {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGALTACONSU_CONSU_VP), hwnd, procAltaConsu);
		}break;

		case ID_LISTCOMP_COMP_VP: {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGLISTCONSU_CONSU_VP), hwnd, procListaConsu);

		}break;

		case ID_EXIT_EXIT_VP: {
			int opc = 0;
			opc = MessageBox(hwnd, "�Est� seguro que quiere salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
			if (opc == 6) {
				DestroyWindow(hwnd);
			}
		}break;

		case ID_CS_EXIT_VP: {
			int opc = 0;
			opc = MessageBox(hwnd, "Quiere cerrar sesion?", "AVISO", MB_YESNO | MB_ICONQUESTION);
			if (opc == 6) {
				EndDialog(hwnd, 0);
				DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAIS), hwnd, procVIS);
				miInfo = nullptr;
				CmiInfo = nullptr;
			}
		}

		}break;
	}


	case WM_DESTROY: {
		PostQuitMessage(0);
	}break;
	}
	return false;
}

LRESULT CALLBACK procAltaUsu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG: {
		SetDlgItemText(hwnd, ID_EDITCOM_ALTA_U, miInfo->comercio);
	case ID_RADADMIN_ALTA_U: {
		SendDlgItemMessage(hwnd, ID_RADADMIN_ALTA_U, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
	}break;

	case ID_RADCAJERO_ALTA_U: {
		SendDlgItemMessage(hwnd, ID_RADCAJERO_ALTA_U, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);

	}break;

	}break;

	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case ID_BUTTREGIS_ALTA_U: {

			char vacio[1] = { "" };
			admin* temp1 = new admin;
			GetDlgItemText(hwnd, ID_EDITNOMU_ALTA_U, temp1->nombre, 50);
			GetDlgItemText(hwnd, ID_EDITCON_ALTA_U, temp1->pass, 50);

			if (IsDlgButtonChecked(hwnd, ID_RADADMIN_ALTA_U) == BST_CHECKED) {
				int charnombre;
				int charespnombre = 0, numnombre = 0, letrasnombre;
				charnombre = strlen(temp1->nombre);

				char equisde[15];
				GetDlgItemText(hwnd, ID_EDITNoUsREGIS, equisde, sizeof(equisde));
				aux = inicio;
				if (charnombre == 0) {
					MessageBox(hwnd, "Ingrese un nombre", "AVISO", MB_OK | MB_ICONERROR);
				}
				else {
					if (charnombre > 15) {
						MessageBox(hwnd, "Su nombre de usuario es muy largo", "AVISO", MB_OK | MB_ICONERROR);
					}
					else {
						for (int i = 0; i < charnombre; i++) {
							if (ispunct(temp1->nombre[i])) {
								charespnombre++;

							}
							if (isdigit(temp1->nombre[i])) {
								numnombre++;
							}
						}
						if (charespnombre != 0 || numnombre != 0) {
							MessageBox(hwnd, "Su nombre no puede contener caracteres no alfanumericos", "AVISO", MB_OK | MB_ICONERROR);
						}
						else {
							charespnombre = 0;
							numnombre = 0;

							while (aux != nullptr && strcmp(aux->nombre, equisde) != 0) {
								aux = aux->sig;
							}
							if (aux != nullptr) {
								MessageBox(hwnd, "Usuario ya existente, ingrese uno valido", "AVISO", MB_OK | MB_ICONERROR);
							}
							else {
								charespnombre = 0;
								numnombre = 0;
								letrasnombre = 0;
								charnombre = strlen(temp1->pass);
								if (charnombre == 0) {
									MessageBox(hwnd, "Ingrese una contrase�a", "AVISO", MB_OK | MB_ICONERROR);
								}
								else {
									if (charnombre < 3 || charnombre > 10) {
										MessageBox(hwnd, "La contrase�a debe incluir una letra, un n�mero y un caracter especial", "AVISO", MB_OK | MB_ICONERROR);
									}
									else {
										for (int i = 0; i < charnombre; i++) {
											if (ispunct(temp1->pass[i])) {
												charespnombre++;
											}
											if (isdigit(temp1->pass[i])) {
												numnombre++;
											}
											if (isalpha(temp1->pass[i])) {
												letrasnombre++;
											}
										}
										if (charespnombre == 0 && numnombre == 0 && letrasnombre == 0) {
											MessageBox(hwnd, "La contrase�a debe incluir una letra, un n�mero y un caracter especial", "AVISO", MB_OK | MB_ICONERROR);
										}
										else {//comercio
											charespnombre = 0;
											numnombre = 0;
											letrasnombre = 0;
											charnombre = strlen(temp1->comercio);
											char equisde[15];
											GetDlgItemText(hwnd, ID_EDITComREGIS, equisde, sizeof(equisde));
											if (charnombre == 0) {
												MessageBox(hwnd, "Ingrese un comercio", "AVISO", MB_OK | MB_ICONERROR);
											}
											else {
												aux = inicio;
												if (charnombre < 5 || charnombre > 15) {
													MessageBox(hwnd, "El comercio debe tener entre 5 y 15 caracteres", "AVISO", MB_OK | MB_ICONERROR);
												}
												else {
													for (int i = 0; i < charnombre; i++) {
														if (ispunct(temp1->comercio[i])) {
															charespnombre++;
														}
														if (isdigit(temp1->comercio[i])) {
															numnombre++;
														}
													}
													if (charespnombre != 0 || numnombre != 0) {
														MessageBox(hwnd, "El comercio no puede contener caracteres no alfanumericos", "AVISO", MB_OK | MB_ICONERROR);
													}
													else {
														strcpy_s(temp1->alias, "");
														strcpy_s(temp1->nombreCompleto, "");
														strcpy_s(temp1->foto, "");

														if (strcmp(temp1->nombre, vacio) == 0 && strcmp(temp1->pass, vacio) == 0 && strcmp(temp1->comercio, vacio) == 0)
														{
															MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
														}
														else {

															aux = inicio;

															if (inicio == nullptr) {
																agregaradmin(temp1);
																SetDlgItemText(hwnd, ID_EDITNOMU_ALTA_U, "");
																SetDlgItemText(hwnd, ID_EDITCON_ALTA_U, "");
																SetDlgItemText(hwnd, ID_EDITCOM_ALTA_U, "");
																delete temp1;
																MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
															}
															else {
																//posible fallo 
																while (aux->sig != nullptr && strcmp(temp1->nombre, aux->nombre) != 0) {
																	aux = aux->sig;
																}
																if (aux->sig == nullptr) {
																	agregaradmin2(temp1);
																	SetDlgItemText(hwnd, ID_EDITNOMU_ALTA_U, "");
																	SetDlgItemText(hwnd, ID_EDITCON_ALTA_U, "");
																	SetDlgItemText(hwnd, ID_EDITCOM_ALTA_U, "");
																	delete temp1;

																	MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
																}
																else {
																	if (strcmp(temp1->pass, aux->pass) == 0) {
																		MessageBox(hwnd, "Usuario ya existente", "AVISO", MB_OK || MB_ICONEXCLAMATION);

																	}

																	else {
																		agregaradmin(temp1);
																		SetDlgItemText(hwnd, ID_EDITNOMU_ALTA_U, "");
																		SetDlgItemText(hwnd, ID_EDITCON_ALTA_U, "");
																		SetDlgItemText(hwnd, ID_EDITCOM_ALTA_U, "");
																		delete temp1;
																		MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
																	}

																}

															}
														}
													}
												}



											}
										}
									}
								}
							}
						}
					}
				}
			}
			else if (IsDlgButtonChecked(hwnd, ID_RADCAJERO_ALTA_U) == BST_CHECKED)
			{
				char vacio[1] = { "" };
				contador* temp2 = new contador;
				GetDlgItemText(hwnd, ID_EDITNOMU_ALTA_U, temp2->Cnombre, 50);
				GetDlgItemText(hwnd, ID_EDITCON_ALTA_U, temp2->Cpass, 50);
				GetDlgItemText(hwnd, ID_EDITCOM_ALTA_U, temp2->Ccomercio, 50);
				int charnombre;
				int charespnombre = 0, numnombre = 0, letrasnombre;
				charnombre = strlen(temp1->nombre);

				char equisde[15];
				GetDlgItemText(hwnd, ID_EDITNoUsREGIS, equisde, sizeof(equisde));
				Caux = Cinicio;

				if (charnombre == 0) {
					MessageBox(hwnd, "Ingrese un nombre", "AVISO", MB_OK | MB_ICONERROR);
				}
				else {
					if (charnombre > 15) {
						MessageBox(hwnd, "Su nombre de usuario es muy largo", "AVISO", MB_OK | MB_ICONERROR);
					}
					else {
						for (int i = 0; i < charnombre; i++) {
							if (ispunct(temp2->Cnombre[i])) {
								charespnombre++;

							}
							if (isdigit(temp2->Cnombre[i])) {
								numnombre++;
							}
						}
						if (charespnombre != 0 || numnombre != 0) {
							MessageBox(hwnd, "Su nombre no puede contener caracteres no alfanumericos", "AVISO", MB_OK | MB_ICONERROR);
						}
						else {
							charespnombre = 0;
							numnombre = 0;

							while (Caux != nullptr && strcmp(Caux->Cnombre, equisde) != 0) {
								Caux = Caux->Csig;
							}
							if (Caux != nullptr) {
								MessageBox(hwnd, "Usuario ya existente, ingrese uno valido", "AVISO", MB_OK | MB_ICONERROR);
							}
							else {
								charespnombre = 0;
								numnombre = 0;
								letrasnombre = 0;
								charnombre = strlen(temp2->Cpass);
								if (charnombre == 0) {
									MessageBox(hwnd, "Ingrese una contrase�a", "AVISO", MB_OK | MB_ICONERROR);
								}
								else {
									if (charnombre < 3 || charnombre > 10) {
										MessageBox(hwnd, "La contrase�a debe incluir una letra, un n�mero y un caracter especial", "AVISO", MB_OK | MB_ICONERROR);
									}
									else {
										for (int i = 0; i < charnombre; i++) {
											if (ispunct(temp2->Cpass[i])) {
												charespnombre++;
											}
											if (isdigit(temp2->Cpass[i])) {
												numnombre++;
											}
											if (isalpha(temp2->Cpass[i])) {
												letrasnombre++;
											}
										}
										if (charespnombre == 0 && numnombre == 0 && letrasnombre == 0) {
											MessageBox(hwnd, "La contrase�a debe tener al menos 3 caracteres", "AVISO", MB_OK | MB_ICONERROR);
										}
										else {//comercio
											charespnombre = 0;
											numnombre = 0;
											letrasnombre = 0;
											charnombre = strlen(temp2->Ccomercio);
											char equisde[15];
											GetDlgItemText(hwnd, ID_EDITComREGIS, equisde, sizeof(equisde));
											if (charnombre == 0) {
												MessageBox(hwnd, "Ingrese un comercio", "AVISO", MB_OK | MB_ICONERROR);
											}
											else {
												aux = inicio;
												if (charnombre < 5 || charnombre > 15) {
													MessageBox(hwnd, "El comercio debe tener entre 5 y 15 caracteres", "AVISO", MB_OK | MB_ICONERROR);
												}
												else {
													for (int i = 0; i < charnombre; i++) {
														if (ispunct(temp2->Ccomercio[i])) {
															charespnombre++;
														}
														if (isdigit(temp2->Ccomercio[i])) {
															numnombre++;
														}
													}
													if (charespnombre != 0 || numnombre != 0) {
														MessageBox(hwnd, "El comercio no puede contener caracteres no alfanumericos", "AVISO", MB_OK | MB_ICONERROR);
													}
													else {
														strcpy_s(temp2->Calias, "");
														strcpy_s(temp2->CnombreCompleto, "");
														strcpy_s(temp2->Cfoto, "");

														if (strcmp(temp2->Cnombre, vacio) == 0 && strcmp(temp2->Cpass, vacio) == 0 && strcmp(temp2->Ccomercio, vacio) == 0)
														{
															MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
														}
														else {

															Caux = Cinicio;

															if (Cinicio == nullptr) {
																agregarcajero(temp2);
																SetDlgItemText(hwnd, ID_EDITNOMU_ALTA_U, "");
																SetDlgItemText(hwnd, ID_EDITCON_ALTA_U, "");
																SetDlgItemText(hwnd, ID_EDITCOM_ALTA_U, "");
																delete temp2;
																MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
															}
															else {
																//posible fallo 
																while (Caux->Csig != nullptr && strcmp(temp2->Cnombre, Caux->Cnombre) != 0) {
																	Caux = Caux->Csig;
																}
																if (Caux->Csig == nullptr) {
																	agregarcajero(temp2);
																	SetDlgItemText(hwnd, ID_EDITNOMU_ALTA_U, "");
																	SetDlgItemText(hwnd, ID_EDITCON_ALTA_U, "");
																	SetDlgItemText(hwnd, ID_EDITCOM_ALTA_U, "");
																	delete temp2;
																	MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
																}
																else {
																	if (strcmp(temp2->Cpass, Caux->Cpass) == 0) {
																		MessageBox(hwnd, "Usuario ya existente", "AVISO", MB_OK || MB_ICONEXCLAMATION);

																	}
																	else {
																		agregarcajero(temp2);
																		SetDlgItemText(hwnd, ID_EDITNOMU_ALTA_U, "");
																		SetDlgItemText(hwnd, ID_EDITCON_ALTA_U, "");
																		SetDlgItemText(hwnd, ID_EDITCOM_ALTA_U, "");
																		delete temp2;
																		MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
																	}
																}
															}
														}
													}
												}


											}
										}
									}
								}
							}
						}
					}
				}


			}

		}break;
		case ID_BUTTREG_ALTA_U: {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), hwnd, procVP);
		}

		}break;


	}
	}
	return false;
}


LRESULT CALLBACK procResetPassUsu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_INITDIALOG: {
		aux = inicio;
		Caux = Cinicio;
		if (miInfo != nullptr) {
			if (Caux == nullptr) {
				while (aux != nullptr) {
					if (strcmp(miInfo->comercio, aux->comercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LISTUSU_RESET), LB_ADDSTRING, 0, (LPARAM)aux->nombre);
					}
					aux = aux->sig;
				}

			}
			else {
				while (aux != nullptr) {
					if (strcmp(miInfo->comercio, aux->comercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LISTUSU_RESET), LB_ADDSTRING, 0, (LPARAM)aux->nombre);
					}
					aux = aux->sig;
				}
				while (Caux != nullptr) {
					if (strcmp(miInfo->comercio, Caux->Ccomercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LISTUSU_RESET), LB_ADDSTRING, 0, (LPARAM)Caux->Cnombre);
					}
					Caux = Caux->Csig;
				}
			}
		}
		else
		{
			if (Caux != nullptr) {

				while (aux != nullptr) {
					if (strcmp(CmiInfo->Ccomercio, aux->comercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LISTUSU_RESET), LB_ADDSTRING, 0, (LPARAM)aux->nombre);
					}
					aux = aux->sig;
				}
				while (Caux != nullptr) {
					if (strcmp(CmiInfo->Ccomercio, Caux->Ccomercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LISTUSU_RESET), LB_ADDSTRING, 0, (LPARAM)Caux->Cnombre);
					}
					Caux = Caux->Csig;
				}
			}

		}

		if (miInfo == nullptr) {
			SetDlgItemText(hwnd, 1049, CmiInfo->Ccomercio);
		}
		else {
			SetDlgItemText(hwnd, 1049, miInfo->comercio);
		}


	}break;

	case WM_COMMAND: {
		if (LOWORD(wParam) == ID_LISTUSU_RESET) {
			switch (HIWORD(wParam)) {
			case LBN_DBLCLK: {
				char textoList[50] = { 0 };
				int indice = 0;

				indice = SendDlgItemMessage(hwnd, ID_LISTUSU_RESET, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, ID_LISTUSU_RESET, LB_GETTEXT, indice, (LPARAM)textoList);

				aux = inicio;
				Caux = Cinicio;
				while (aux != nullptr && strcmp(textoList, aux->nombre) != 0) {
					aux = aux->sig;
				}
				if (aux == nullptr)
				{
					while (Caux != nullptr && strcmp(textoList, Caux->Cnombre) != 0) {
						Caux = Caux->Csig;
					}
					if (Caux == nullptr)
					{

					}
					else if (strcmp(textoList, Caux->Cnombre) == 0) {
						SetDlgItemText(hwnd, ID_EDITCONTRA_RESET, Caux->Cpass);
						SetDlgItemText(hwnd, ID_STATIC_RESETTYPE, "Cajero");
					}

				}
				else if (strcmp(textoList, aux->nombre) == 0) {

					SetDlgItemText(hwnd, ID_EDITCONTRA_RESET, aux->pass);
					SetDlgItemText(hwnd, ID_STATIC_RESETTYPE, "Administrador");
				}



			}break;
			}
		}
		if (LOWORD(wParam) == ID_BUTTSAVE_RESET) {

			admin* temp1 = new admin;
			if (aux != nullptr) {
				strcpy_s(temp1->nombre, aux->nombre);

			}
			contador* temp2 = new contador;
			if (Caux != nullptr) {
				strcpy_s(temp2->Cnombre, Caux->Cnombre);

			}
			char contra[50] = { 0 };
			char newcontra[50] = { 0 };
			char nombre[50] = { 0 };
			char nombreC[50] = { 0 };

			GetDlgItemText(hwnd, ID_EDITCONTRA_RESET, contra, 50);
			GetDlgItemText(hwnd, ID_EDITNEWCON_RESET, newcontra, 50);

			if (aux != nullptr) {
				strcpy_s(nombre, aux->nombre);

			}
			if (Caux != nullptr) {
				strcpy_s(nombreC, Caux->Cnombre);

			}

			if (strcmp("", newcontra) == 0) {
				MessageBox(hwnd, "Ingrese nueva contrase�a ", "AVISO", MB_OK || MB_ICONINFORMATION);

			}
			else {
				if (strcmp(temp1->nombre, nombre) == 0)
				{
					SetDlgItemText(hwnd, ID_EDITCONTRA_RESET, "");
					SetDlgItemText(hwnd, ID_EDITNEWCON_RESET, "");
					strcpy_s(temp1->pass, newcontra);
					modificar(temp1, nombre);
					MessageBox(hwnd, "Nueva contrase�a registrada", "AVISO", MB_OK || MB_ICONINFORMATION);
				}

				else if (strcmp(temp2->Cnombre, nombreC) == 0)
				{
					SetDlgItemText(hwnd, ID_EDITCONTRA_RESET, "");
					SetDlgItemText(hwnd, ID_EDITNEWCON_RESET, "");
					strcpy_s(temp2->Cpass, newcontra);
					modificarC(temp2, nombreC);
					MessageBox(hwnd, "Nueva contrase�a registrada", "AVISO", MB_OK || MB_ICONINFORMATION);

				}
			}

		}
		if (LOWORD(wParam) == ID_BUTTReg_RESET) {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), hwnd, procVP);
		}
	}
	}

	return false;
}





LRESULT CALLBACK procListUsu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG: {
		aux = inicio;
		Caux = Cinicio;
		if (miInfo != nullptr) {
			if (Caux == nullptr) {
				while (aux != nullptr) {
					if (strcmp(miInfo->comercio, aux->comercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LIST_LISTU), LB_ADDSTRING, 0, (LPARAM)aux->nombre);
					}
					aux = aux->sig;
				}

			}
			else {
				while (aux != nullptr) {
					if (strcmp(miInfo->comercio, aux->comercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LIST_LISTU), LB_ADDSTRING, 0, (LPARAM)aux->nombre);
					}
					aux = aux->sig;
				}
				while (Caux != nullptr) {
					if (strcmp(miInfo->comercio, Caux->Ccomercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LIST_LISTU), LB_ADDSTRING, 0, (LPARAM)Caux->Cnombre);
					}
					Caux = Caux->Csig;
				}
			}
		}
		else
		{
			if (Caux != nullptr) {

				while (aux != nullptr) {
					if (strcmp(CmiInfo->Ccomercio, aux->comercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LIST_LISTU), LB_ADDSTRING, 0, (LPARAM)aux->nombre);
					}
					aux = aux->sig;
				}
				while (Caux != nullptr) {
					if (strcmp(CmiInfo->Ccomercio, Caux->Ccomercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LIST_LISTU), LB_ADDSTRING, 0, (LPARAM)Caux->Cnombre);
					}
					Caux = Caux->Csig;
				}
			}

		}

		if (miInfo == nullptr) {
			SetDlgItemText(hwnd, ID_EDITCOM_LISTU, CmiInfo->Ccomercio);
		}
		else {
			SetDlgItemText(hwnd, ID_EDITCOM_LISTU, miInfo->comercio);
		}
	}break;


	case WM_COMMAND: {
		if (LOWORD(wParam) == ID_LIST_LISTU) { //if(LOWORD(wParam) == ID_LISTUSU_RESET)
			switch (HIWORD(wParam)) {
			case LBN_DBLCLK: {
				char textoList[50] = { 0 };
				int indice = 0;

				indice = SendDlgItemMessage(hwnd, ID_LIST_LISTU, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, ID_LIST_LISTU, LB_GETTEXT, indice, (LPARAM)textoList);

				aux = inicio;
				Caux = Cinicio;
				while (aux != nullptr && strcmp(textoList, aux->nombre) != 0) {
					aux = aux->sig;
				}
				if (aux == nullptr)
				{
					while (Caux != nullptr && strcmp(textoList, Caux->Cnombre) != 0) {
						Caux = Caux->Csig;
					}
					if (Caux == nullptr)
					{

					}
					else if (strcmp(textoList, Caux->Cnombre) == 0) {
						HBITMAP bmp; //1
						bmp = (HBITMAP)LoadImage(NULL, Caux->Cfoto, IMAGE_BITMAP, 80, 110, LR_LOADFROMFILE); //2
						SendDlgItemMessage(hwnd, ID_PCICBMP_LISTU, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 	
						SetDlgItemText(hwnd, ID_STATICNOMCOM_LISTU, Caux->CnombreCompleto);
						SetDlgItemText(hwnd, ID_STATICALIAS_LISTU, Caux->Calias);
						SetDlgItemText(hwnd, ID_STATICNOMU_ALTA_U, "Cajero");
						SetDlgItemText(hwnd, ID_EDITTYPE_LISTU, "Cajero");

					}

				}
				else if (strcmp(textoList, aux->nombre) == 0) {

					HBITMAP bmp; //1
					bmp = (HBITMAP)LoadImage(NULL, aux->foto, IMAGE_BITMAP, 80, 110, LR_LOADFROMFILE); //2
					SendDlgItemMessage(hwnd, ID_PCICBMP_LISTU, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 	
					SetDlgItemText(hwnd, ID_STATICNOMCOM_LISTU, aux->nombreCompleto);
					SetDlgItemText(hwnd, ID_STATICALIAS_LISTU, aux->alias);
					SetDlgItemText(hwnd, ID_STATICNOMU_ALTA_U, "Administrador");
					SetDlgItemText(hwnd, ID_EDITTYPE_LISTU, "Administrador");

				}



			}break;
			}
		}
		if (LOWORD(wParam) == ID_BUTTUPDATE_LISTU) {
			if (aux != nullptr) {

				aux2 = aux;
				EndDialog(hwnd, 0);
				DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_MODIFY_MOD_LISTU), hwnd, procModifiyListU);
			}
			else if (Caux != nullptr) {
				Caux2 = Caux;
				EndDialog(hwnd, 0);
				DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_MODIFY_MOD_LISTU), hwnd, procModifiyListU);
			}
			else {
				MessageBox(hwnd, "Seleccione un usuario ", "AVISO", MB_YESNO || MB_ICONINFORMATION);
			}


		}
		if (LOWORD(wParam) == ID_BUTTELI_LISTU) {

			int opc = 0;
			opc = MessageBox(hwnd, "Eliminar usuario?", "AVISO", MB_YESNO || MB_ICONINFORMATION);
			if (opc == 1) {
				char nombre[50] = { 0 };
				char nombreleiminar[50] = { 0 };
				GetDlgItemText(hwnd, ID_EDITTYPE_LISTU, nombre, sizeof(nombre));
				if (strcmp(nombre, "Administrador") == 0 && aux != nullptr) {
					strcpy_s(nombreleiminar, aux->nombre);
					eliminar(nombreleiminar);
				}
				else if (strcmp(nombre, "Cajero") == 0 && Caux != nullptr) {
					strcpy_s(nombreleiminar, Caux->Cnombre);
					eliminarC(nombreleiminar);
				}
				else {
					MessageBox(hwnd, "Seleccione un usuario", "AVISO", MB_OK || MB_ICONINFORMATION);
				}
			}

		}
		if (LOWORD(wParam) == ID_BUTTREG_LISTU) { //if(LOWORD(wParam) == ID_BUTTReg_RESET:
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), hwnd, procVP);
		}


	}
	}
	return false;
}

LRESULT CALLBACK procModifiyListU(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG: {
		if (aux2 != nullptr) {
			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, aux->foto, IMAGE_BITMAP, 80, 110, LR_LOADFROMFILE); //2
			SendDlgItemMessage(hwnd, ID_PCICBMP_LISTU, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 	
			SetDlgItemText(hwnd, ID_STATICNOMCOM_LISTU, aux->nombreCompleto);
			SetDlgItemText(hwnd, ID_STATICALIAS_LISTU, aux->alias);
		}
		else if (Caux2 != nullptr) {
			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, Caux->Cfoto, IMAGE_BITMAP, 80, 110, LR_LOADFROMFILE); //2
			SendDlgItemMessage(hwnd, ID_EDITAMOD_LISTU, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 	
			SetDlgItemText(hwnd, ID_EDITNOMMOD_LISTU, Caux->CnombreCompleto);
			SetDlgItemText(hwnd, ID_EDITAMOD_LISTU, Caux->Calias);
		}
		else {
			SetDlgItemText(hwnd, ID_EDITNOMMOD_LISTU, "");
			SetDlgItemText(hwnd, ID_EDITAMOD_LISTU, "");
		}


	}break;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case ID_BUTTPHOTOMOD_LISTU: {

			OPENFILENAME ofn;

			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "ALL\0 * .*\0Bitmaps\0 * .bmp\0";
			ofn.lpstrFile = zFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(zFile);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.nFilterIndex = 2;
			//selecccione
			if (GetOpenFileName(&ofn) == TRUE) {
				HBITMAP bmp; //1

				bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 130, 150, LR_LOADFROMFILE); //2

				SendDlgItemMessage(hwnd, ID_STAPIC_MOD_LISTU, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 

			}
			else {
				//Si el usuario no seleccion� una imagen, qu� se debe de hacer?
			}
		}break;
		case ID_BUTTSAVEMOD_LISTU: {
			admin* temp2 = new admin;
			contador* temp3 = new contador;
			char vacio[1] = { 0 };

			if (aux != nullptr) {
				if (strcmp(aux->nombreCompleto, "") == 0) {

					GetDlgItemText(hwnd, ID_EDITNOMMOD_LISTU, temp2->nombreCompleto, sizeof(temp2->nombreCompleto));
					GetDlgItemText(hwnd, ID_EDITAMOD_LISTU, temp2->alias, sizeof(temp2->alias));
					GetDlgItemText(hwnd, ID_STAPIC_MOD_LISTU, temp2->foto, sizeof(temp2->foto));
					if (strcmp(temp2->nombreCompleto, vacio) == 0 && strcmp(temp2->foto, vacio) == 0)
					{
						MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
					}
					else {

						strcpy_s(aux->nombreCompleto, temp2->nombreCompleto);
						strcpy_s(aux->alias, temp2->alias);
						strcpy_s(aux->foto, zFile);
						EnableWindow(GetDlgItem(hwnd, ID_EDITNOMMOD_LISTU), false);
						EnableWindow(GetDlgItem(hwnd, ID_EDITAMOD_LISTU), false);
						EnableWindow(GetDlgItem(hwnd, ID_STAPIC_MOD_LISTU), false);
						MessageBox(hwnd, "Se ha actualizado el usuario", "AVISO", MB_OK || MB_ICONEXCLAMATION);



					}
				}
				else {
					char nombrecompleto[50] = { 0 };
					char nomalias[50] = { 0 };
					char foto[MAX_PATH] = { 0 };

					GetDlgItemText(hwnd, ID_EDITNOMMOD_LISTU, nombrecompleto, sizeof(nombrecompleto));
					GetDlgItemText(hwnd, ID_EDITAMOD_LISTU, nomalias, sizeof(nomalias));
					GetDlgItemText(hwnd, ID_STAPIC_MOD_LISTU, foto, sizeof(foto));

					if (strcmp(nombrecompleto, vacio) == 0 && strcmp(foto, vacio) == 0)
					{
						MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
					}

					else {
						strcpy_s(aux->nombreCompleto, nombrecompleto);
						strcpy_s(aux->alias, foto);
						strcpy_s(aux->foto, zFile);
						EnableWindow(GetDlgItem(hwnd, ID_EDITNOMMOD_LISTU), false);
						EnableWindow(GetDlgItem(hwnd, ID_EDITAMOD_LISTU), false);
						EnableWindow(GetDlgItem(hwnd, ID_STAPIC_MOD_LISTU), false);
						MessageBox(hwnd, "Se ha actualizado el usuario", "AVISO", MB_OK || MB_ICONEXCLAMATION);

					}
				}
			}
			else if (Caux != nullptr)
			{
				if (strcmp(Caux->CnombreCompleto, "") == 0) {

					GetDlgItemText(hwnd, ID_EDITNOMMOD_LISTU, temp3->CnombreCompleto, sizeof(temp3->CnombreCompleto));
					GetDlgItemText(hwnd, ID_EDITAMOD_LISTU, temp3->Calias, sizeof(temp3->Calias));
					GetDlgItemText(hwnd, ID_STAPIC_MOD_LISTU, temp3->Cfoto, sizeof(temp3->Cfoto));
					if (strcmp(temp3->CnombreCompleto, vacio) == 0 && strcmp(temp3->Cfoto, vacio) == 0)
					{
						MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
					}
					else {

						strcpy_s(Caux->CnombreCompleto, temp3->CnombreCompleto);
						strcpy_s(Caux->Calias, temp3->Calias);
						strcpy_s(Caux->Cfoto, zFile);
						EnableWindow(GetDlgItem(hwnd, ID_EDITNOMMOD_LISTU), false);
						EnableWindow(GetDlgItem(hwnd, ID_EDITAMOD_LISTU), false);
						EnableWindow(GetDlgItem(hwnd, ID_STAPIC_MOD_LISTU), false);
						MessageBox(hwnd, "Se ha actualizado el usuario", "AVISO", MB_OK || MB_ICONEXCLAMATION);


					}
				}
				else {
					char nombrecompleto[50] = { 0 };
					char nomalias[50] = { 0 };
					char foto[MAX_PATH] = { 0 };

					GetDlgItemText(hwnd, ID_EDITNOMMOD_LISTU, nombrecompleto, sizeof(nombrecompleto));
					GetDlgItemText(hwnd, ID_EDITAMOD_LISTU, nomalias, sizeof(nomalias));
					GetDlgItemText(hwnd, ID_STAPIC_MOD_LISTU, foto, sizeof(foto));
					if (strcmp(nombrecompleto, "") == 0 && strcmp(foto, "") == 0)
					{
						MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
					}

					else {
						strcpy_s(Caux->CnombreCompleto, nombrecompleto);
						strcpy_s(Caux->Calias, nomalias);
						strcpy_s(Caux->Cfoto, zFile);
						EnableWindow(GetDlgItem(hwnd, ID_EDITNOMMOD_LISTU), false);
						EnableWindow(GetDlgItem(hwnd, ID_EDITAMOD_LISTU), false);
						EnableWindow(GetDlgItem(hwnd, ID_STAPIC_MOD_LISTU), false);
						MessageBox(hwnd, "Se ha actualizado el usuario", "AVISO", MB_OK || MB_ICONEXCLAMATION);

					}
				}
			}
			else {
				MessageBox(hwnd, "Error", "AVISO", MB_OK || MB_ICONERROR);

			}

		}break;

		case ID_BUTTREGMOD_LISTU: {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGLISTU_U_VP), hwnd, procListUsu);
		}break;
		}
	}break;
	}
	return false;
}

LRESULT CALLBACK procAltaCli(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG: {
		SYSTEMTIME fechaHoy;
		ZeroMemory(&fechaHoy, sizeof(fechaHoy));
		GetLocalTime(&fechaHoy);

		char fechaCompleta[11] = { 0 };
		char fechaChar[5] = { 0 };

		sprintf_s(fechaChar, "%d", fechaHoy.wYear); //Convertir de int a char

		strcat_s(fechaCompleta, fechaChar); //Concateno
		strcat_s(fechaCompleta, "/");

		sprintf_s(fechaChar, "%d", fechaHoy.wMonth);

		strcat_s(fechaCompleta, fechaChar);
		strcat_s(fechaCompleta, "/");

		sprintf_s(fechaChar, "%d", fechaHoy.wDay);

		strcat_s(fechaCompleta, fechaChar);

		SetDlgItemText(hwnd, ID_EDITDATE_ALTACL, fechaCompleta);

		if (ClmiInfo != nullptr) {
			SetDlgItemText(hwnd, ID_EDITNOMCO_ALTACL, ClmiInfo->Clnombre);
			SetDlgItemText(hwnd, ID_EDITAL_ALTACL, ClmiInfo->Clalias);
			SetDlgItemText(hwnd, ID_EDITTEL_ALTACL, ClmiInfo->telefono);
			SetDlgItemText(hwnd, ID_EDITEMAIL_ALTACL, ClmiInfo->correo);

		}

		if (miInfo != nullptr) {
			SetDlgItemText(hwnd, ID_EDITCOM_ALTACL, miInfo->comercio);

		}
		else if (CmiInfo != nullptr)
		{
			SetDlgItemText(hwnd, ID_EDITCOM_ALTACL, CmiInfo->Ccomercio);

		}

		//SetWindowText(GetDlgItem(hwnd, IDC_s1), fechaCompleta);
	}break;

	case WM_COMMAND: {
		switch (LOWORD(wParam)) {

		case ID_SAVE_ALTACL: {
			char vacio[1] = { "" };
			cliente* temp3 = new cliente;
			GetDlgItemText(hwnd, ID_EDITNOMCO_ALTACL, temp3->Clnombre, 50);
			GetDlgItemText(hwnd, ID_EDITAL_ALTACL, temp3->Clalias, 50);
			GetDlgItemText(hwnd, ID_EDITTEL_ALTACL, temp3->telefono, 50);
			GetDlgItemText(hwnd, ID_EDITEMAIL_ALTACL, temp3->correo, 50);
			GetDlgItemText(hwnd, ID_EDITCOM_ALTACL, temp3->Clcomercio, 50);
			int charnombre;
			int charespnombre = 0, numnombre = 0, letrasnombre;
			charnombre = strlen(temp3->Clnombre);

			char equisde[15];
			GetDlgItemText(hwnd, ID_EDITNoUsREGIS, equisde, sizeof(equisde));
			aux = inicio;
			if (charnombre == 0) {
				MessageBox(hwnd, "Ingrese un nombre", "AVISO", MB_OK | MB_ICONERROR);
			}
			else {
				if (charnombre > 15) {
					MessageBox(hwnd, "El nombre de usuario sobrepasa los caracteres", "AVISO", MB_OK | MB_ICONERROR);
				}
				else {
					for (int i = 0; i < charnombre; i++) {
						if (ispunct(temp3->Clnombre[i])) {
							charespnombre++;

						}
						if (isdigit(temp3->Clnombre[i])) {
							numnombre++;
						}
					}
					if (charespnombre != 0 || numnombre != 0) {
						MessageBox(hwnd, "Su nombre no puede contener caracteres no alfanumericos", "AVISO", MB_OK | MB_ICONERROR);
					}
					else {
						charespnombre = 0;
						numnombre = 0;

						while (Claux != nullptr && strcmp(Claux->Clnombre, equisde) != 0) {
							Claux = Claux->Clsig;
						}
						if (Claux != nullptr) {
							MessageBox(hwnd, "Usuario ya existente, ingrese uno valido", "AVISO", MB_OK | MB_ICONERROR);
						}
						else {
							charespnombre = 0;
							numnombre = 0;
							letrasnombre = 0;
							charnombre = strlen(temp3->telefono);
							if (charnombre == 0) {
								MessageBox(hwnd, "Ingrese una telefono", "AVISO", MB_OK | MB_ICONERROR);
							}
							else {
								if (charnombre != 10) {
									MessageBox(hwnd, "telefono no valida", "AVISO", MB_OK | MB_ICONERROR);
								}
								else {
									for (int i = 0; i < charnombre; i++) {

										if (isdigit(temp3->telefono[i])) {
											numnombre++;
										}
									}
									if (numnombre != charnombre) {
										MessageBox(hwnd, "telefono no valida", "AVISO", MB_OK | MB_ICONERROR);
									}
									else {//comercio
										charespnombre = 0;
										numnombre = 0;
										letrasnombre = 0;
										charnombre = strlen(temp3->Clalias);
										char equisde[15];
										GetDlgItemText(hwnd, ID_EDITComREGIS, equisde, sizeof(equisde));
										if (charnombre == 0) {
											MessageBox(hwnd, "Ingrese un Alias", "AVISO", MB_OK | MB_ICONERROR);
										}
										else {
											aux = inicio;
											if (charnombre < 5 || charnombre > 15) {
												MessageBox(hwnd, "El Alias debe tener entre 5 y 15 caracteres", "AVISO", MB_OK | MB_ICONERROR);
											}
											else {
												for (int i = 0; i < charnombre; i++) {
													if (ispunct(temp3->Clcomercio[i])) {
														charespnombre++;
													}

												}
												if (charespnombre != 0) {
													MessageBox(hwnd, "El Alias no puede contener caracteres no alfanumericos", "AVISO", MB_OK | MB_ICONERROR);
												}
												else {
													if (ClmiInfo == nullptr) {



														if (strcmp(temp3->Clnombre, vacio) == 0 && strcmp(temp3->telefono, vacio) == 0 && strcmp(temp3->correo, vacio) == 0)
														{
															MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
														}
														else {

															Claux = Clinicio;

															if (Claux == nullptr) {
																agregarcliente(temp3);
																SetDlgItemText(hwnd, ID_EDITNOMCO_ALTACL, "");
																SetDlgItemText(hwnd, ID_EDITAL_ALTACL, "");
																SetDlgItemText(hwnd, ID_EDITTEL_ALTACL, "");
																SetDlgItemText(hwnd, ID_EDITEMAIL_ALTACL, "");

																delete temp3;

																MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
															}
															else {
																//posible fallo 
																while (Claux->Clsig != nullptr && strcmp(temp3->Clnombre, Claux->Clnombre) != 0) {
																	Claux = Claux->Clsig;
																}
																if (Claux->Clsig == nullptr) {
																	agregarcliente(temp3);
																	SetDlgItemText(hwnd, ID_EDITNOMCO_ALTACL, "");
																	SetDlgItemText(hwnd, ID_EDITAL_ALTACL, "");
																	SetDlgItemText(hwnd, ID_EDITTEL_ALTACL, "");
																	SetDlgItemText(hwnd, ID_EDITEMAIL_ALTACL, "");

																	delete temp3;
																	MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
																}
																else {
																	if (strcmp(temp3->correo, Claux->correo) == 0) {
																		MessageBox(hwnd, "Usuario ya existente", "AVISO", MB_OK || MB_ICONEXCLAMATION);

																	}
																	else {
																		agregarcliente(temp3);
																		SetDlgItemText(hwnd, ID_EDITNOMCO_ALTACL, "");
																		SetDlgItemText(hwnd, ID_EDITAL_ALTACL, "");
																		SetDlgItemText(hwnd, ID_EDITTEL_ALTACL, "");
																		SetDlgItemText(hwnd, ID_EDITEMAIL_ALTACL, "");
																		delete temp3;
																		MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
																	}

																}

															}
														}
													}
													else {
														char vacio[1] = { "" };
														char nombre[50] = { 0 };
														cliente* temp3 = new cliente;
														GetDlgItemText(hwnd, ID_EDITNOMCO_ALTACL, temp3->Clnombre, 50);
														strcpy_s(nombre, temp3->Clnombre);
														GetDlgItemText(hwnd, ID_EDITAL_ALTACL, temp3->Clalias, 50);
														GetDlgItemText(hwnd, ID_EDITTEL_ALTACL, temp3->telefono, 50);
														GetDlgItemText(hwnd, ID_EDITEMAIL_ALTACL, temp3->correo, 50);
														GetDlgItemText(hwnd, ID_EDITCOM_ALTACL, temp3->Clcomercio, 50);
														if (strcmp(temp3->Clnombre, vacio) == 0 && strcmp(temp3->telefono, vacio) == 0 && strcmp(temp3->correo, vacio) == 0)
														{
															MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
														}
														else {

															Claux = Clinicio;

															if (Claux == nullptr) {
																modificarCl(temp3, nombre);
																SetDlgItemText(hwnd, ID_EDITNOMCO_ALTACL, "");
																SetDlgItemText(hwnd, ID_EDITAL_ALTACL, "");
																SetDlgItemText(hwnd, ID_EDITTEL_ALTACL, "");
																SetDlgItemText(hwnd, ID_EDITEMAIL_ALTACL, "");

																delete temp3;
																MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
															}
															else {
																//posible fallo 
																while (Claux->Clsig != nullptr && strcmp(temp3->Clnombre, Claux->Clnombre) != 0) {
																	Claux = Claux->Clsig;
																}
																if (Claux->Clsig == nullptr) {
																	modificarCl(temp3, nombre);
																	SetDlgItemText(hwnd, ID_EDITNOMCO_ALTACL, "");
																	SetDlgItemText(hwnd, ID_EDITAL_ALTACL, "");
																	SetDlgItemText(hwnd, ID_EDITTEL_ALTACL, "");
																	SetDlgItemText(hwnd, ID_EDITEMAIL_ALTACL, "");
																	delete temp3;
																}
																else {
																	if (strcmp(temp3->correo, Claux->correo) == 0) {
																		MessageBox(hwnd, "Correo ya en uso", "AVISO", MB_OK || MB_ICONEXCLAMATION);

																	}
																	else {
																		modificarCl(temp3, nombre);
																		SetDlgItemText(hwnd, ID_EDITNOMCO_ALTACL, "");
																		SetDlgItemText(hwnd, ID_EDITAL_ALTACL, "");
																		SetDlgItemText(hwnd, ID_EDITTEL_ALTACL, "");
																		SetDlgItemText(hwnd, ID_EDITEMAIL_ALTACL, "");
																		delete temp3;
																	}

																}

															}
														}

													}
												}
											}



										}
									}
								}
							}
						}
					}
				}
			}



		}break;
		case ID_BUTTREG_ALTACL: {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), hwnd, procVP);
		}break;
		}
	}break;
	}
	return false;
}
LRESULT CALLBACK procListaCli(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG: {
		aux = inicio;
		Claux = Clinicio;
		if (miInfo != nullptr) {
			if (Claux != nullptr) {
				while (Claux != nullptr) {
					if (strcmp(miInfo->comercio, Claux->Clcomercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LIST_LISTCL), LB_ADDSTRING, 0, (LPARAM)Claux->Clnombre);
					}
					Claux = Claux->Clsig;
				}

			}
		}
		else
		{
			if (Claux != nullptr) {
				while (Claux != nullptr) {
					if (strcmp(CmiInfo->Ccomercio, Claux->Clcomercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LIST_LISTCL), LB_ADDSTRING, 0, (LPARAM)Claux->Clnombre);
					}
					Claux = Claux->Clsig;
				}

			}

		}

		if (miInfo == nullptr) {
			SetDlgItemText(hwnd, ID_EDITCOM_LISTCL, CmiInfo->Ccomercio);
		}
		else {
			SetDlgItemText(hwnd, ID_EDITCOM_LISTCL, miInfo->comercio);
		}

	}break;
	case WM_COMMAND: {
		if (LOWORD(wParam) == ID_LIST_LISTCL) { //if(LOWORD(wParam) == ID_LISTUSU_RESET)
			switch (HIWORD(wParam)) {
			case LBN_DBLCLK: {
				char textoList[50] = { 0 };
				int indice = 0;

				indice = SendDlgItemMessage(hwnd, ID_LIST_LISTCL, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, ID_LIST_LISTCL, LB_GETTEXT, indice, (LPARAM)textoList);


				Claux = Clinicio;

				while (Claux != nullptr && strcmp(textoList, Claux->Clnombre) != 0) {
					Claux = Claux->Clsig;
				}
				if (Claux == nullptr)
				{

				}
				else if (strcmp(textoList, Claux->Clnombre) == 0) {


					SetDlgItemText(hwnd, ID_EDITALIAS_LISTCL, Claux->Clalias);
					SetDlgItemText(hwnd, ID_EDITTEL_LISTCL, Claux->telefono);
					SetDlgItemText(hwnd, ID_EDITEMAIL_LISTCL, Claux->correo);


				}



			}break;
			}
		}
		if (LOWORD(wParam) == ID_BUTTUPDATE_LISTCL) {
			if (Claux != nullptr) {

				ClmiInfo = Claux;
				EndDialog(hwnd, 0);
				//agregrar nueva ventana 
				DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGALTACLI_CLI_VP), hwnd, procAltaCli);
			}
			else {
				MessageBox(hwnd, "Seleccione un usuario ", "AVISO", MB_YESNO || MB_ICONINFORMATION);
			}


		}
		if (LOWORD(wParam) == ID_BUTTELI_LISTCL) {

			int opc = 0;
			opc = MessageBox(hwnd, "Desea eliminar el usuario?", "AVISO", MB_YESNO || MB_ICONINFORMATION);
			if (opc == 1) {
				char nombreleiminar[50] = { 0 };
				if (Claux != nullptr) {
					strcpy_s(nombreleiminar, Claux->Clnombre);
					eliminarCl(nombreleiminar);
				}
				else {
					MessageBox(hwnd, "Seleccione un usuario", "AVISO", MB_OK || MB_ICONINFORMATION);
				}
			}

		}
		if (LOWORD(wParam) == ID_BUTTREG_LISTCL) {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), hwnd, procVP);
		}break;
	}break;

	}
	return false;
}

LRESULT CALLBACK procAltaPro(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG: {
		SYSTEMTIME fechaHoy;
		ZeroMemory(&fechaHoy, sizeof(fechaHoy));
		GetLocalTime(&fechaHoy);

		char fechaCompleta[11] = { 0 };
		char fechaChar[5] = { 0 };

		sprintf_s(fechaChar, "%d", fechaHoy.wYear); //Convertir de int a char

		strcat_s(fechaCompleta, fechaChar); //Concateno
		strcat_s(fechaCompleta, "/");

		sprintf_s(fechaChar, "%d", fechaHoy.wMonth);

		strcat_s(fechaCompleta, fechaChar);
		strcat_s(fechaCompleta, "/");

		sprintf_s(fechaChar, "%d", fechaHoy.wDay);

		strcat_s(fechaCompleta, fechaChar);

		SetDlgItemText(hwnd, ID_EDITDATE_ALTAPRO, fechaCompleta);


		if (promiinfo != nullptr) {

			//%d conversiones de int a char 
			//%p conversiones de int a char con punteros 

			SetDlgItemText(hwnd, ID_EDITNOMCO_ALTACL, promiinfo->pronombre);
			SetDlgItemInt(hwnd, ID_EDITMONTO_ALTAPRO, (UINT)promiinfo->pmonto, false);
			SetDlgItemInt(hwnd, ID_EDITMONTO_ALTAPRO, (UINT)promiinfo->porcentajedes, false);

			//GetDlgItemInt()
			if (promiinfo->estatus == 0) { //Activa
				SendDlgItemMessage(hwnd, ID_RADIOACTIVE_ALTAPRO, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);

			}
			else if (promiinfo->estatus == 1) { //Inactiva
				SendDlgItemMessage(hwnd, ID_RADINACTIVE_ALTAPRO, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
			}
		}

		if (miInfo != nullptr) {
			SetDlgItemText(hwnd, ID_EDITCOM_ALTAPRO, miInfo->comercio);

		}
		else if (CmiInfo != nullptr)
		{
			SetDlgItemText(hwnd, ID_EDITCOM_ALTAPRO, CmiInfo->Ccomercio);

		}


	}break;

	case WM_COMMAND: {
		switch (LOWORD(wParam)) {

		case ID_BUTTSAVE_ALTAPRO: {

			char vacio[1] = { "" };
			promociones* temp4 = new promociones;
			BOOL num, porcentaje;

			GetDlgItemText(hwnd, ID_EDITNOMPRO_ALTAPRO, temp4->pronombre, 50);
			GetDlgItemText(hwnd, ID_EDITCOM_ALTAPRO, temp4->Clcomercio, 50);
			temp4->pmonto = GetDlgItemInt(hwnd, ID_EDITMONTO_ALTAPRO, &num, false);
			temp4->porcentajedes = GetDlgItemInt(hwnd, ID_EDITPORDES_ALTAPRO, &porcentaje, false);

			if (IsDlgButtonChecked(hwnd, ID_RADIOACTIVE_ALTAPRO) == BST_CHECKED)
			{
				temp4->estatus = 0;

			}
			else if (IsDlgButtonChecked(hwnd, ID_RADINACTIVE_ALTAPRO) == BST_CHECKED)
			{
				temp4->estatus = 1;
			}

			int charnombre;
			int charespnombre = 0, numnombre = 0, letrasnombre;
			charnombre = strlen(temp4->pronombre);

			char equisde[15];
			GetDlgItemText(hwnd, ID_EDITNoUsREGIS, equisde, sizeof(equisde));
			aux = inicio;
			if (charnombre == 0) {
				MessageBox(hwnd, "Ingrese un nombre", "AVISO", MB_OK | MB_ICONERROR);
			}
			else {
				if (charnombre > 15) {
					MessageBox(hwnd, "Su nombre de usuario es muy largo", "AVISO", MB_OK | MB_ICONERROR);
				}
				else {
					for (int i = 0; i < charnombre; i++) {
						if (ispunct(temp4->pronombre[i])) {
							charespnombre++;

						}
						if (isdigit(temp4->pronombre[i])) {
							numnombre++;
						}
					}
					if (charespnombre != 0 || numnombre != 0) {
						MessageBox(hwnd, "Su nombre no puede contener caracteres no alfanumericos", "AVISO", MB_OK | MB_ICONERROR);
					}
					else {
						charespnombre = 0;
						numnombre = 0;

						while (proaux != nullptr && strcmp(proaux->pronombre, equisde) != 0) {
							proaux = proaux->prosig;
						}
						if (proaux != nullptr) {
							MessageBox(hwnd, "Usuario ya existente, ingrese uno valido", "AVISO", MB_OK | MB_ICONERROR);
						}
						else {
							char j[10] = { 0 };
							sprintf_s(j, "%d", temp4->pmonto);

							charespnombre = 0;
							numnombre = 0;
							letrasnombre = 0;
							charnombre = strlen(j);
							if (charnombre == 0) {
								MessageBox(hwnd, "Ingrese un Monto", "AVISO", MB_OK | MB_ICONERROR);
							}
							else {
								if (temp4->pmonto < 100) {
									MessageBox(hwnd, "Monto no valido", "AVISO", MB_OK | MB_ICONERROR);
								}
								else {
									for (int i = 0; i < charnombre; i++) {
										if (isdigit(j[i])) {
											numnombre++;
										}

									}
									if (numnombre != charnombre) {
										MessageBox(hwnd, "Monto no valido", "AVISO", MB_OK | MB_ICONERROR);
									}
									else {


										char k[50] = { 0 };

										sprintf_s(k, "%p", temp4->porcentajedes);

										charespnombre = 0;
										numnombre = 0;
										letrasnombre = 0;
										charnombre = strlen(k);
										char equisde[15];
										GetDlgItemText(hwnd, ID_EDITComREGIS, equisde, sizeof(equisde));
										if (charnombre == 0) {
											MessageBox(hwnd, "Ingrese un porcentaje", "AVISO", MB_OK | MB_ICONERROR);
										}
										else {
											aux = inicio;
											if (charnombre <= 0 || charnombre > 100) {
												MessageBox(hwnd, "El porcentaje debe tener entre 5 y 15 caracteres", "AVISO", MB_OK | MB_ICONERROR);
											}
											else {
												for (int i = 0; i < charnombre; i++) {
													if (isdigit(k[i])) {
														numnombre++;
													}

												}
												if (charnombre != numnombre) {
													MessageBox(hwnd, "El porcentaje no puede contener caracteres no alfanumericos", "AVISO", MB_OK | MB_ICONERROR);
												}
												else {

													if (promiinfo == nullptr) {
														if (strcmp(temp4->pronombre, vacio) == 0)
														{
															MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
														}
														else {

															proaux = proinicio;

															if (proaux == nullptr) {
																agregarpromo(temp4);
																SetDlgItemText(hwnd, ID_EDITNOMPRO_ALTAPRO, "");
																SetDlgItemText(hwnd, ID_EDITMONTO_ALTAPRO, "");
																SetDlgItemText(hwnd, ID_EDITPORDES_ALTAPRO, "");

																delete temp4;
																MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
															}
															else {

																while (proaux->prosig != nullptr && strcmp(temp4->pronombre, proaux->pronombre) != 0) {
																	proaux = proaux->prosig;
																}
																if (proaux->prosig == nullptr) {
																	agregarpromo(temp4);
																	SetDlgItemText(hwnd, ID_EDITNOMPRO_ALTAPRO, "");
																	SetDlgItemText(hwnd, ID_EDITMONTO_ALTAPRO, "");
																	SetDlgItemText(hwnd, ID_EDITPORDES_ALTAPRO, "");
																	delete temp4;
																	MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
																}
																else {

																	agregarpromo(temp4);
																	SetDlgItemText(hwnd, ID_EDITNOMPRO_ALTAPRO, "");
																	SetDlgItemText(hwnd, ID_EDITMONTO_ALTAPRO, "");
																	SetDlgItemText(hwnd, ID_EDITPORDES_ALTAPRO, "");
																	delete temp4;
																	MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);

																}

															}
														}
													}



													else {
														char vacio[1] = { "" };
														char nombre[50] = { 0 };
														promociones* temp4 = new promociones;
														BOOL num, porcentaje;




														GetDlgItemText(hwnd, ID_EDITNOMPRO_ALTAPRO, temp4->pronombre, 50);
														strcpy_s(nombre, temp4->pronombre);
														GetDlgItemText(hwnd, ID_EDITCOM_ALTAPRO, temp4->Clcomercio, 50);
														temp4->pmonto = GetDlgItemInt(hwnd, ID_EDITMONTO_ALTAPRO, &num, false);
														temp4->porcentajedes = GetDlgItemInt(hwnd, ID_EDITMONTO_ALTAPRO, &porcentaje, false);
														if (IsDlgButtonChecked(hwnd, ID_RADIOACTIVE_ALTAPRO) == BST_CHECKED)
														{
															temp4->estatus = 0;

														}
														else if (IsDlgButtonChecked(hwnd, ID_RADINACTIVE_ALTAPRO) == BST_CHECKED)
														{
															temp4->estatus = 1;
														}
														if (strcmp(temp4->pronombre, vacio) == 0)
														{
															MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
														}
														else {

															proaux = proinicio;

															if (proaux == nullptr) {
																strcpy_s(nombre, temp4->pronombre);
																modificarpromocion(temp4, nombre);
																SetDlgItemText(hwnd, ID_EDITNOMPRO_ALTAPRO, "");
																SetDlgItemText(hwnd, ID_EDITMONTO_ALTAPRO, "");
																SetDlgItemText(hwnd, ID_EDITPORDES_ALTAPRO, "");

																delete temp4;
																MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
															}
															else {
																//posible fallo 
																while (proaux->prosig != nullptr && strcmp(temp4->pronombre, proaux->pronombre) != 0) {
																	proaux = proaux->prosig;
																}
																if (proaux->prosig == nullptr) {
																	strcpy_s(nombre, temp4->pronombre);
																	modificarpromocion(temp4, nombre);
																	SetDlgItemText(hwnd, ID_EDITNOMPRO_ALTAPRO, "");
																	SetDlgItemText(hwnd, ID_EDITMONTO_ALTAPRO, "");
																	SetDlgItemText(hwnd, ID_EDITPORDES_ALTAPRO, "");
																	delete temp4;
																}
																else {

																	strcpy_s(nombre, temp4->pronombre);
																	modificarpromocion(temp4, nombre);
																	SetDlgItemText(hwnd, ID_EDITNOMPRO_ALTAPRO, "");
																	SetDlgItemText(hwnd, ID_EDITMONTO_ALTAPRO, "");
																	SetDlgItemText(hwnd, ID_EDITPORDES_ALTAPRO, "");
																	delete temp4;

																}

															}
														}

													}
												}
											}



										}
									}
								}
							}
						}
					}
				}
			}

		}break;
		case ID_BUTTREG_ALTAPRO: {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), hwnd, procVP);
		}break;
		}
	}break;
	}
	return false;
}
LRESULT CALLBACK procListaPro(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG: {
		aux = inicio;
		proaux = proinicio;
		if (miInfo != nullptr) {
			if (proaux != nullptr) {
				while (proaux != nullptr) {
					if (strcmp(miInfo->comercio, proaux->Clcomercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LIST_LISTPRO), LB_ADDSTRING, 0, (LPARAM)proaux->pronombre);
					}
					proaux = proaux->prosig;
				}

			}
		}
		else if (CmiInfo != nullptr)
		{
			if (proaux != nullptr) {
				while (proaux != nullptr) {
					if (strcmp(CmiInfo->Ccomercio, proaux->Clcomercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LIST_LISTPRO), LB_ADDSTRING, 0, (LPARAM)proaux->pronombre);
					}
					proaux = proaux->prosig;
				}

			}

		}

		if (miInfo == nullptr) {
			if (CmiInfo != nullptr) {
				SetDlgItemText(hwnd, ID_EDITCOM_LISTPRO, CmiInfo->Ccomercio);
			}
		}
		else {
			SetDlgItemText(hwnd, ID_EDITCOM_LISTPRO, miInfo->comercio);
		}

	}break;
	case WM_COMMAND: {
		if (LOWORD(wParam) == ID_LIST_LISTPRO) { //if(LOWORD(wParam) == ID_LISTUSU_RESET)
			switch (HIWORD(wParam)) {
			case LBN_DBLCLK: {
				char textoList[50] = { 0 };
				int indice = 0;

				indice = SendDlgItemMessage(hwnd, ID_LIST_LISTPRO, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, ID_LIST_LISTPRO, LB_GETTEXT, indice, (LPARAM)textoList);


				proaux = proinicio;

				while (proaux != nullptr && strcmp(textoList, proaux->pronombre) != 0) {
					proaux = proaux->prosig;
				}
				if (proaux == nullptr)
				{

				}
				else if (strcmp(textoList, proaux->pronombre) == 0) {

					char estatus[50] = { "Activa" };
					char estatusi[50] = { "Iactiva" };
					SetDlgItemInt(hwnd, ID_EDITMONTO_LISTPRO, (UINT)proaux->pmonto, false);
					if (proaux->estatus == 0)
					{

						SetDlgItemText(hwnd, ID_EDITSTATUS_LISTPRO, estatus);
					}
					else if (proaux->estatus == 1) {

						SetDlgItemText(hwnd, ID_EDITSTATUS_LISTPRO, estatusi);
					}


					SetDlgItemInt(hwnd, ID_EDITPORDES_LISTPRO, (UINT)proaux->porcentajedes, false);
				}

			}break;
			}
		}
		if (LOWORD(wParam) == ID_BUTTUPDATE_LISTPRO) {
			if (proaux != nullptr) {

				promiinfo = proaux;
				EndDialog(hwnd, 0);
				//agregrar nueva ventana 
				DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGALTAPRO_PRO_VP), hwnd, procAltaPro);
			}
			else {
				MessageBox(hwnd, "Seleccione un usuario ", "AVISO", MB_YESNO || MB_ICONINFORMATION);
			}


		}
		if (LOWORD(wParam) == ID_BUTTDELETE_LISTPRO) {

			int opc = 0;
			opc = MessageBox(hwnd, "Desea eliminar el usuario?", "AVISO", MB_YESNO || MB_ICONINFORMATION);
			if (opc == 1) {
				char nombreleiminar[50] = { 0 };
				if (proaux != nullptr) {
					strcpy_s(nombreleiminar, proaux->pronombre);
					eliminarpromo(nombreleiminar);
				}
				else {
					MessageBox(hwnd, "Seleccione un usuario", "AVISO", MB_OK || MB_ICONINFORMATION);
				}
			}

		}
		if (LOWORD(wParam) == ID_BUTTREG_LISTPRO) {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), hwnd, procVP);
		}break;
	}break;

	}
	return false;
}

LRESULT CALLBACK procAltaConsu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	char f[50] = { 0 };
	char CLIENTES[50] = { 0 };

	int opc = 0;
	int  decuento, subtotal, total, desaplified;
	int monto = 0;
	int totalmonto = 0;
	int* j;
	int charespnombre = 0, letrasnombre = 0, numnombre = 0;
	int charnombre = 0;
	char k[50] = { 0 };

	switch (msg) {

	case WM_INITDIALOG: {
		SYSTEMTIME fechaHoy;
		ZeroMemory(&fechaHoy, sizeof(fechaHoy));
		GetLocalTime(&fechaHoy);

		char fechaCompleta[30] = { 0 };
		char fechaChar[5] = { 0 };

		char fcehadate[50] = { 0 };
		char fcehaexacta[50] = { 0 };

		sprintf_s(fechaChar, "%d", fechaHoy.wYear); //Convertir de int a char

		strcat_s(fechaCompleta, fechaChar); //Concateno
		strcat_s(fechaCompleta, "/");

		sprintf_s(fechaChar, "%d", fechaHoy.wMonth);

		strcat_s(fechaCompleta, fechaChar);
		strcat_s(fechaCompleta, "/");

		sprintf_s(fechaChar, "%d", fechaHoy.wDay);

		strcat_s(fechaCompleta, fechaChar);
		strcat_s(fechaCompleta, "        ");

		sprintf_s(fcehadate, "%d", fechaHoy.wHour);
		strcat_s(fcehaexacta, fcehadate);
		strcat_s(fcehaexacta, ":");

		sprintf_s(fcehadate, "%d", fechaHoy.wMinute);
		strcat_s(fcehaexacta, fcehadate);
		strcat_s(fcehaexacta, ":");

		sprintf_s(fcehadate, "%d", fechaHoy.wSecond);
		strcat_s(fcehaexacta, fcehadate);

		SetDlgItemText(hwnd, ID_EDITDATE_ALTACONSU, fechaCompleta);
		SetDlgItemText(hwnd, ID_NODATE_ALTACONSU, fcehaexacta);




		if (miInfo != nullptr) {
			SetDlgItemText(hwnd, ID_EDITCOM_ALTACONSU, miInfo->comercio);

		}
		else if (CmiInfo != nullptr)
		{
			SetDlgItemText(hwnd, ID_EDITCOM_ALTACONSU, CmiInfo->Ccomercio);

		}

		aux = inicio;
		Claux = Clinicio;
		if (miInfo != nullptr) {
			if (Claux != nullptr) {
				while (Claux != nullptr) {
					if (strcmp(miInfo->comercio, Claux->Clcomercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LIST_ALTACONSU), LB_ADDSTRING, 0, (LPARAM)Claux->Clnombre);
					}
					Claux = Claux->Clsig;
				}

			}
		}
		else if (CmiInfo != nullptr)
		{
			if (Claux != nullptr) {
				while (Claux != nullptr) {
					if (strcmp(CmiInfo->Ccomercio, Claux->Clcomercio) == 0) {
						SendMessage(GetDlgItem(hwnd, ID_LIST_ALTACONSU), LB_ADDSTRING, 0, (LPARAM)Claux->Clnombre);
					}
					Claux = Claux->Clsig;
				}

			}

		}

	}break;

	case WM_COMMAND: {
		switch (LOWORD(wParam)) {

		case ID_LIST_ALTACONSU: {
			switch (HIWORD(wParam)) {
			case LBN_DBLCLK: {
				char textoList[50] = { 0 };
				int indice = 0;

				indice = SendDlgItemMessage(hwnd, ID_LIST_ALTACONSU, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, ID_LIST_ALTACONSU, LB_GETTEXT, indice, (LPARAM)textoList);

				Claux = Clinicio;

				while (Claux != nullptr)
				{
					if (strcmp(textoList, Claux->Clnombre) == 0) {

						SetDlgItemText(hwnd, ID_EDITCLI_ALTACONSU, Claux->Clnombre);
						GetDlgItemText(hwnd, ID_EDITCLI_ALTACONSU, f, sizeof(f));

					}
					Claux = Claux->Clsig;
				}

			}break;
			}
		}break;

		case ID_BUTTCHECK_ALTACONSU: {

			BOOL montoK, descuentok, subtotalk, totalk, desapply;
			coaux = comincio;
			proaux = proinicio;

			//j = &CLIENTES; 
//seleccione un usuario

			GetDlgItemText(hwnd, ID_EDITCLI_ALTACONSU, f, 50);
			monto = GetDlgItemInt(hwnd, ID_EDITMON_ALTACONSU, &montoK, FALSE);
			//toa(sizeof(monto), k, monto);
			sprintf_s(k, "%d", monto);

			charespnombre = 0;
			numnombre = 0;
			letrasnombre = 0;
			charnombre = strlen(k);

			if (charnombre == 0) {
				MessageBox(hwnd, "Ingrese un comercio", "AVISO", MB_OK | MB_ICONERROR);
			}
			else {
				aux = inicio;
				if (charnombre == 150000) {
					MessageBox(hwnd, "El comercio debe tener entre 5 y 15 caracteres", "AVISO", MB_OK | MB_ICONERROR);
				}
				else {
					for (int i = 0; i < charnombre; i++) {
						if (ispunct(k[i])) {
							charespnombre++;
						}
						if (isalpha(k[i])) {
							letrasnombre++;
						}
					}
					if (charespnombre != 0 || numnombre != 0) {
						MessageBox(hwnd, "El comercio no puede contener caracteres no alfanumericos", "AVISO", MB_OK | MB_ICONERROR);
					}
					else {
						if (proaux == nullptr) {
							if (charespnombre != 0)
							{
								MessageBox(hwnd, "Llene los campos requeridos", "AVISO", MB_OK || MB_ICONEXCLAMATION);
							}
							else {
								MessageBox(hwnd, "No hay promciones validadas en este momento", "AVISO", MB_OK || MB_ICONINFORMATION);
								opc = MessageBox(hwnd, "Quiere conitnuar?", "AVISO", MB_YESNO);
								if (opc == 6)
								{
									subtotal = monto;
									total = subtotal + (subtotal * .16);
									SetDlgItemInt(hwnd, ID_EDITSUB_ALTACONSU, (UINT)subtotal, FALSE);
									SetDlgItemInt(hwnd, ID_EDITTOTAL_ALTACONSU, (UINT)total, FALSE);
								}
								else { //en caso de no 
									MessageBox(hwnd, "Agregue promociones ", "", MB_OK || MB_ICONEXCLAMATION);
									DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGALTAPRO_PRO_VP), hwnd, procAltaPro);

								}
							}
						}
						else
						{
							if (monto != 0) {
								if (coaux != nullptr) {
									if (proaux != nullptr) {
										while (proaux != nullptr)
										{

											while (coaux != nullptr) {

												modificartotalconsumo(f, totalmonto);

											}

											if (coaux == nullptr)
											{
												if (proaux->pmonto == *montoTotal) {
													int opc = 0;
													MessageBox(hwnd, "El cliente cumple con el monto para la promocion", "AVISO", MB_OK || MB_ICONINFORMATION);
													opc = MessageBox(hwnd, "Desea aplicar?", "PROMOCION", MB_YESNO);
													if (opc == 6) {
														if (proaux != nullptr) {
															SetDlgItemInt(hwnd, ID_EDITDES_ALTACONSU, (UINT)proaux->porcentajedes, FALSE);
															subtotal = monto - (monto * (proaux->porcentajedes / 100));
															total = subtotal + (subtotal * .16);
															SetDlgItemInt(hwnd, ID_EDITSUB_ALTACONSU, (UINT)subtotal, FALSE);
															SetDlgItemInt(hwnd, ID_EDITTOTAL_ALTACONSU, (UINT)total, FALSE);
															proaux = nullptr;

														}
														else
														{
															MessageBox(hwnd, "No cumple con el monto", "AVISO", MB_OK);
														}
													}
													else
													{

														subtotal = monto;
														total = subtotal + (subtotal * .16);
														SetDlgItemInt(hwnd, ID_EDITSUB_ALTACONSU, (UINT)subtotal, FALSE);
														SetDlgItemInt(hwnd, ID_EDITTOTAL_ALTACONSU, (UINT)total, FALSE);
														proaux = nullptr;

													}
												}
												else
												{
													coaux == comincio;
													proaux = proaux->prosig;
												}

											}
										}

										desaplified = GetDlgItemInt(hwnd, ID_EDITDES_ALTACONSU, &desapply, FALSE);
										if (desaplified == 0) {

											if (coaux == nullptr && proaux == nullptr) {
												MessageBox(hwnd, "El cliete no cumple con el moonto valido para la promociones", "AVISO", MB_OK);
												opc = MessageBox(hwnd, "Quiere conitnuar?", "AVISO", MB_YESNO);
												if (opc == 6)
												{
													subtotal = monto;
													total = subtotal + (subtotal * .16);
													SetDlgItemInt(hwnd, ID_EDITSUB_ALTACONSU, (UINT)subtotal, FALSE);
													SetDlgItemInt(hwnd, ID_EDITTOTAL_ALTACONSU, (UINT)total, FALSE);
												}
												else { //en caso de no 
													MessageBox(hwnd, "Agregue promociones ", "", MB_OK || MB_ICONEXCLAMATION);
													DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGALTAPRO_PRO_VP), hwnd, procAltaPro);

												}
											}
										}



									}
									else
									{

										MessageBox(hwnd, "No hay promciones validadas en este momento", "AVISO", MB_OK || MB_ICONINFORMATION);
										opc = MessageBox(hwnd, "Quiere conitnuar?", "AVISO", MB_YESNO);
										if (opc == 6)
										{
											subtotal = monto;
											total = subtotal + (subtotal * .16);
											SetDlgItemInt(hwnd, ID_EDITSUB_ALTACONSU, (UINT)subtotal, FALSE);
											SetDlgItemInt(hwnd, ID_EDITTOTAL_ALTACONSU, (UINT)total, FALSE);
										}
										else { //en caso de no 
											MessageBox(hwnd, "Agregue promociones ", "", MB_OK || MB_ICONEXCLAMATION);
											DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGALTAPRO_PRO_VP), hwnd, procAltaPro);

										}
									}
								}
								else

								{
									subtotal = monto;
									total = subtotal + (subtotal * .16);
									SetDlgItemInt(hwnd, ID_EDITSUB_ALTACONSU, (UINT)subtotal, FALSE);
									SetDlgItemInt(hwnd, ID_EDITTOTAL_ALTACONSU, (UINT)total, FALSE);
								}

							}
							else {
								MessageBox(hwnd, "Anexe monto ", "AVISO", MB_OK || MB_ICONINFORMATION);

							}


						}

					}

				}break;



		case ID_BUTTSAVE_ALTACONSU: {

			if (promiinfo == nullptr) {
				char vacio[1] = { "" };
				compras* temp5 = new compras;
				BOOL num, porcentaje, sub, total;


				GetDlgItemText(hwnd, ID_EDITCOM_ALTACONSU, temp5->Comcomercio, 50);
				GetDlgItemText(hwnd, ID_EDITDATE_ALTACONSU, temp5->fecha, 50);
				GetDlgItemText(hwnd, ID_NODATE_ALTACONSU, temp5->fechaexacta, 50);
				GetDlgItemText(hwnd, ID_EDITCLI_ALTACONSU, temp5->cliente, 50);
				GetDlgItemText(hwnd, ID_EDITCLI_ALTACONSU, temp5->cliente, 50);
				strcpy_s(temp5->fechaexacta, ""),
					//strcpy_s(temp5->cliente, f); 
					temp5->monto = GetDlgItemInt(hwnd, ID_EDITMON_ALTACONSU, &num, FALSE);
				temp5->descuento = GetDlgItemInt(hwnd, ID_EDITDES_ALTACONSU, &porcentaje, FALSE);
				temp5->subtotal = GetDlgItemInt(hwnd, ID_EDITSUB_ALTACONSU, &sub, FALSE);
				temp5->total = GetDlgItemInt(hwnd, ID_EDITTOTAL_ALTACONSU, &total, FALSE);

				if (strcmp(temp5->Comcomercio, "") == 0) {
					MessageBox(hwnd, "Seleccione el comercio", "AVISO", MB_OK || MB_ICONINFORMATION);
				}
				else //registrar consumo
				{
					coaux = comincio;
					Claux = Clinicio;
					if (coaux == nullptr) {
						agregarconsumos(temp5);
						SetDlgItemText(hwnd, ID_EDITMON_ALTACONSU, "");
						SetDlgItemText(hwnd, ID_EDITDES_ALTACONSU, "");
						SetDlgItemText(hwnd, ID_EDITCLI_ALTACONSU, "");
						SetDlgItemText(hwnd, ID_EDITSUB_ALTACONSU, "");
						SetDlgItemText(hwnd, ID_EDITTOTAL_ALTACONSU, "");
						delete temp5;
						MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
					}
					else {
						//posible fallo 
						while (coaux->cosig != nullptr) {
							coaux = coaux->cosig;
						}
						if (coaux->cosig == nullptr) {
							agregarconsumos(temp5);

							SetDlgItemText(hwnd, ID_EDITMON_ALTACONSU, "");
							SetDlgItemText(hwnd, ID_EDITDES_ALTACONSU, "");
							SetDlgItemText(hwnd, ID_EDITCLI_ALTACONSU, "");
							SetDlgItemText(hwnd, ID_EDITSUB_ALTACONSU, "");
							SetDlgItemText(hwnd, ID_EDITTOTAL_ALTACONSU, "");
							delete temp5;
							MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);
						}
						else {
							agregarconsumos(temp5);

							SetDlgItemText(hwnd, ID_EDITMON_ALTACONSU, "");
							SetDlgItemText(hwnd, ID_EDITDES_ALTACONSU, "");
							SetDlgItemText(hwnd, ID_EDITCLI_ALTACONSU, "");
							SetDlgItemText(hwnd, ID_EDITSUB_ALTACONSU, "");
							SetDlgItemText(hwnd, ID_EDITTOTAL_ALTACONSU, "");
							delete temp5;
							MessageBox(hwnd, "Se ha registrado exitosamente", "Registrado", MB_OK || MB_ICONINFORMATION);

						}

					}
				}

			}

		}break;
		case ID_BUTTRES_ALTACONSU: {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), hwnd, procVP);
		}break;
			}
		}break;

		}
	}
	}
	return false;

}

LRESULT CALLBACK procListaConsu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG: {
		aux = inicio;
		coaux = comincio;
		if (miInfo != nullptr) {
			if (coaux != nullptr) {
				while (coaux != nullptr) {
					if (strcmp(miInfo->comercio, coaux->Comcomercio) == 0) {
						char fecha[50] = { 0 };
						char fechaexacta[50] = { 0 };
						strcpy_s(fecha, coaux->fecha);
						strcpy_s(fechaexacta, coaux->fechaexacta);
						strcat_s(fecha, fechaexacta);
						strcpy_s(coaux->fechaultima, fecha);

						SendMessage(GetDlgItem(hwnd, ID_LIST_LISTCONSU), LB_ADDSTRING, 0, (LPARAM)fecha);
					}
					coaux = coaux->cosig;
				}

			}
		}
		else if (CmiInfo != nullptr)
		{
			if (coaux != nullptr) {
				while (coaux != nullptr) {
					if (strcmp(CmiInfo->Ccomercio, coaux->Comcomercio) == 0) {
						char fecha[50] = { 0 };
						char fechaexacta[50] = { 0 };
						strcpy_s(fecha, coaux->fecha);
						strcpy_s(fechaexacta, coaux->fechaexacta);
						strcat_s(fecha, fechaexacta);
						strcpy_s(coaux->fechaultima, fecha);

						SendMessage(GetDlgItem(hwnd, ID_LIST_LISTCONSU), LB_ADDSTRING, 0, (LPARAM)fecha);
					}
					coaux = coaux->cosig;
				}

			}

		}

		if (miInfo == nullptr) {
			if (CmiInfo != nullptr) {
				SetDlgItemText(hwnd, ID_EDITCOM_LISTCONSU, CmiInfo->Ccomercio);
			}
		}
		else {
			SetDlgItemText(hwnd, ID_EDITCOM_LISTCONSU, miInfo->comercio);
		}

	}break;

	case WM_COMMAND: {
		if (LOWORD(wParam) == ID_LIST_LISTCONSU) { //if(LOWORD(wParam) == ID_LISTUSU_RESET)
			switch (HIWORD(wParam)) {
			case LBN_DBLCLK: {
				char textoList[50] = { 0 };
				int indice = 0;

				indice = SendDlgItemMessage(hwnd, ID_LIST_LISTCONSU, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, ID_LIST_LISTCONSU, LB_GETTEXT, indice, (LPARAM)textoList);


				coaux = comincio;
				if (strcmp(textoList, "") == 0) {
					MessageBox(hwnd, "Seleccione un usuario", "AVISO", MB_OK || MB_ICONEXCLAMATION);
				}
				else {
					while (coaux != nullptr && strcmp(textoList, coaux->fechaultima) != 0) {
						coaux = coaux->cosig;
					}
					if (coaux == nullptr)
					{

					}
					else if (strcmp(textoList, coaux->fechaultima) == 0) {

						SetDlgItemInt(hwnd, ID_EDITMON_LISTCONSU, (UINT)coaux->monto, false);
						SetDlgItemInt(hwnd, ID_EDITSUB_LISTCONSU, (UINT)coaux->descuento, false);
						SetDlgItemInt(hwnd, ID_EDITMONTO_LISTPRO, (UINT)coaux->subtotal, false);
						SetDlgItemInt(hwnd, ID_EDITTOTAL_LISTCONSU, (UINT)coaux->total, false);

					}
				}


			}break;
			}
		}
		if (LOWORD(wParam) == ID_BUTTREG_LISTCONSU) {
			EndDialog(hwnd, 0);
			DialogBox(hInstGlobal, MAKEINTRESOURCE(ID_DIAGVP), hwnd, procVP);
		}
	}break;
	}
	return false;
}




void agregaradmin(admin* nuevo)
{
	if (inicio == nullptr) {
		inicio = new admin;
		aux = inicio;
		strcpy_s(aux->nombre, nuevo->nombre);
		strcpy_s(aux->pass, nuevo->pass);
		strcpy_s(aux->comercio, nuevo->comercio);
		strcpy_s(aux->nombreCompleto, nuevo->nombreCompleto);
		strcpy_s(aux->foto, nuevo->foto);
		strcpy_s(aux->alias, nuevo->alias);

		aux->ant = nullptr;
		aux->sig = nullptr;

	}
	else {
		while (aux->sig != nullptr) {
			aux = aux->sig;
		}
		aux->sig = new admin;
		aux->sig->ant = aux;
		aux = aux->sig;
		aux->sig = nullptr;

		strcpy_s(aux->nombre, nuevo->nombre);
		strcpy_s(aux->pass, nuevo->pass);
		strcpy_s(aux->comercio, nuevo->comercio);
		strcpy_s(aux->foto, nuevo->foto);
		strcpy_s(aux->nombreCompleto, nuevo->nombreCompleto);
		strcpy_s(aux->alias, nuevo->alias);

	}

	//MessageBox(NULL, "Se ha registrado exitosamente", "AVISO", MB_OK | MB_ICONERROR);
}

//cambiar funcion en procVr en caso de fallo
void agregaradmin2(admin* nuevo) {
	if (aux->sig == nullptr) {
		aux->sig = new admin;
		aux->sig->ant = aux;
		aux = aux->sig;
		aux->sig = nullptr;


		strcpy_s(aux->nombre, nuevo->nombre);
		strcpy_s(aux->pass, nuevo->pass);
		strcpy_s(aux->comercio, nuevo->comercio);
		strcpy_s(aux->foto, nuevo->foto);
		strcpy_s(aux->nombreCompleto, nuevo->nombreCompleto);
		strcpy_s(aux->alias, nuevo->alias);
	}
}


void modificar(admin* newInfo, char nomUsuario[50])
{
	aux = inicio;
	//char newNom[50];

	if (aux == nullptr)
	{
		MessageBox(0, "No hay Usuario registrados", "AVISO", MB_OK | MB_ICONINFORMATION);
	}
	else {
		while (aux != nullptr && strcmp(aux->nombre, nomUsuario) != 0) {
			aux = aux->sig;
		}
		if (aux == nullptr) {
			MessageBox(0, "Usuario no encontrado", "AVISO", MB_OK | MB_ICONINFORMATION);
		}
		else {

			strcpy_s(aux->pass, newInfo->pass);

			MessageBox(0, "Se modific� exitosamente", "AVISO", MB_OK | MB_ICONINFORMATION);

		}
	}
}


void eliminar(char nomUsu[50])
{
	aux = inicio;

	if (aux == nullptr)
	{
		MessageBox(0, "La lista esta vacia. Agregue Usuario", "AVISO", MB_OK);
	}
	else {
		while (aux != nullptr && strcmp(aux->nombre, nomUsu) != 0) { //Nos movemos en el arreglo para buscar la cancion

			aux = aux->sig;
		}
		if (aux == nullptr) {
			MessageBox(0, "No encontrado", "AVISO", MB_OK);
		}
		else if (aux == inicio) {	//El nodo es el primero 

			if (aux->sig == nullptr) { //Si es el primero y unico nodo
				//delete aux;		//Eliminamos el primer nodo
				//inicio = nullptr;
				//aux = inicio;

				inicio = nullptr;
				delete aux;
				aux = inicio;
			}
			else { //Si es el primero y hay mas nodos

				//inicio = aux->sig;	//Cambiamos el puntero 'inicio' al segundo nodo, que ahora es nuestro primer elemento
				//delete aux;			//Eliminamos el primer nodo		
				//aux = inicio;			//Para que aux no quede sin apuntar a nada, la apuntamos al inicio
				//aux->ant = nullptr;

				inicio = inicio->sig;
				aux->sig->ant = nullptr;
				delete aux;
				aux = inicio;

			}

			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK);
		}
		else {

			if (aux->sig == nullptr) { //Si el nodo es el �ltimo
				aux->ant->sig = nullptr;	//Antes de eliminar, el penultumo nodo, su puntero siguiente, lo igualamos a nullptr
				delete aux;
				aux = inicio;
			}
			else { //Si es cualquier nodo que no sea el inicio o el �ltimo
				aux->sig->ant = aux->ant;
				aux->ant->sig = aux->sig;
				delete aux;
				aux = inicio; //Para que aux no quede sin apuntar a nada, la apuntamos al inicio
			}

			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK);

		}
	}

}


void escribirUsuario() {
	aux = inicio;

	ofstream usuarios;
	usuarios.open("ARCHIVOESTESI", ios::out | ios::binary | ios::trunc);

	if (usuarios.is_open()) {
		if (aux == inicio) {
			while (aux != nullptr)
			{
				usuarios.write((char*)aux, sizeof(admin));
				aux = aux->sig;

			}
		}

	}
	usuarios.close();
}



void leerUsuario() {
	ifstream leerusu;
	leerusu.open("ARCHIVOESTESI", ios::in | ios::binary);

	aux = inicio;
	if (leerusu.is_open()) {

		admin* usuLeido = new admin;


		if (aux == inicio) {
			while (!leerusu.read((char*)usuLeido, sizeof(admin)).eof()) {

				while (aux != nullptr && aux->sig != nullptr)
				{
					aux = aux->sig;
				}
				if (aux == nullptr) {
					inicio = usuLeido;
					inicio->sig = nullptr;
					inicio->ant = nullptr;
					aux = inicio;
				}
				else {
					aux->sig = usuLeido;
					aux->sig->ant = aux;
					aux = aux->sig;
					aux->sig = nullptr;
				}

				usuLeido = new admin;
			}
		}

	}
}

//Cajero
void agregarcajero(contador* Cnuevo)
{
	if (Cinicio == nullptr) {
		Cinicio = new contador;
		Caux = Cinicio;
		strcpy_s(Caux->Cnombre, Cnuevo->Cnombre);
		strcpy_s(Caux->Cpass, Cnuevo->Cpass);
		strcpy_s(Caux->Ccomercio, Cnuevo->Ccomercio);
		strcpy_s(Caux->CnombreCompleto, Cnuevo->CnombreCompleto);
		strcpy_s(Caux->Cfoto, Cnuevo->Cfoto);
		strcpy_s(Caux->Calias, Cnuevo->Calias);

		Caux->Cant = nullptr;
		Caux->Csig = nullptr;

	}
	else {
		while (Caux->Csig != nullptr) {
			Caux = Caux->Csig;
		}
		Caux->Csig = new contador;
		Caux->Csig->Cant = Caux;
		Caux = Caux->Csig;
		Caux->Csig = nullptr;

		strcpy_s(Caux->Cnombre, Cnuevo->Cnombre);
		strcpy_s(Caux->Cpass, Cnuevo->Cpass);
		strcpy_s(Caux->Ccomercio, Cnuevo->Ccomercio);
		strcpy_s(Caux->CnombreCompleto, Cnuevo->CnombreCompleto);
		strcpy_s(Caux->Cfoto, Cnuevo->Cfoto);
		strcpy_s(Caux->Calias, Cnuevo->Calias);


	}
}
//agregar nuevos parametros 
void modificarC(contador* newInfo, char nomUsuario[50])
{
	Caux = Cinicio;
	//char newNom[50];

	if (Caux == nullptr)
	{
		MessageBox(0, "No hay Usuario registrados", "AVISO", MB_OK | MB_ICONINFORMATION);
	}
	else {
		while (Caux != nullptr && strcmp(Caux->Cnombre, nomUsuario) != 0) {
			Caux = Caux->Csig;
		}
		if (Caux == nullptr) {
			MessageBox(0, "Usuario no encontrado", "AVISO", MB_OK | MB_ICONINFORMATION);
		}
		else {

			strcpy_s(Caux->Cpass, newInfo->Cpass);

			MessageBox(0, "Usuario modificado", "AVISO", MB_OK | MB_ICONINFORMATION);

		}
	}
}

void eliminarC(char nomUsu[50])
{
	Caux = Cinicio;

	if (Caux == nullptr)
	{
		MessageBox(0, "La lista esta vacia. Agregue Usuario", "AVISO", MB_OK);
	}
	else {
		while (Caux != nullptr && strcmp(Caux->Cnombre, nomUsu) != 0) { //Nos movemos en el arreglo para buscar la cancion

			Caux = Caux->Csig;
		}
		if (Caux == nullptr) {
			MessageBox(0, "No encontrado", "AVISO", MB_OK);
		}
		else if (Caux == Cinicio) {	//El nodo es el primero 

			if (Caux->Csig == nullptr) { //Si es el primero y unico nodo
				//delete Caux;		//Eliminamos el primer nodo
				//Cinicio = nullptr;
				//Caux = Cinicio;

				Cinicio = nullptr;
				delete Caux;
				Caux = Cinicio;
			}
			else { //Si es el primero y hay mas nodos

				//Cinicio = Caux->sig;	//Cambiamos el puntero 'Cinicio' al segundo nodo, que ahora es nuestro primer elemento
				//delete Caux;			//Eliminamos el primer nodo		
				//Caux = Cinicio;			//Para que Caux no quede sin apuntar a nada, la apuntamos al Cinicio
				//Caux->ant = nullptr;

				Cinicio = Cinicio->Csig;
				Caux->Csig->Cant = nullptr;
				delete Caux;
				Caux = Cinicio;

			}

			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK);
		}
		else {

			if (Caux->Csig == nullptr) { //Si el nodo es el �ltimo
				Caux->Cant->Csig = nullptr;	//Antes de eliminar, el penultumo nodo, su puntero siguiente, lo igualamos a nullptr
				delete Caux;
				Caux = Cinicio;
			}
			else { //Si es cualquier nodo que no sea el Cinicio o el �ltimo
				Caux->Csig->Cant = Caux->Cant;
				Caux->Cant->Csig = Caux->Csig;
				delete Caux;
				Caux = Cinicio; //Para que Caux no quede sin apuntar a nada, la apuntamos al Cinicio
			}

			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK);

		}
	}

}


void escribircajero() {
	Caux = Cinicio;

	ofstream usuarios;
	usuarios.open("ARCHIVOESTESI", ios::out | ios::binary | ios::trunc);

	if (usuarios.is_open()) {
		if (Caux == Cinicio) {
			while (Caux != nullptr)
			{
				usuarios.write((char*)Caux, sizeof(contador));
				Caux = Caux->Csig;

			}
		}

	}
	usuarios.close();
}

void leercajero() {
	ifstream leerusu;
	leerusu.open("ARCHIVOESTESI", ios::in | ios::binary);

	aux = inicio;
	if (leerusu.is_open()) {

		contador* usuLeido = new contador;


		if (Caux == Cinicio) {
			while (!leerusu.read((char*)usuLeido, sizeof(contador)).eof()) {

				while (Caux != nullptr && Caux->Csig != nullptr)
				{
					Caux = Caux->Csig;
				}
				if (Caux == nullptr) {
					Cinicio = usuLeido;
					Cinicio->Csig = nullptr;
					Cinicio->Cant = nullptr;
					Caux = Cinicio;
				}
				else {
					Caux->Csig = usuLeido;
					Caux->Csig->Cant = Caux;
					Caux = Caux->Csig;
					Caux->Csig = nullptr;
				}

				usuLeido = new contador;
			}
		}

	}
}

//Cliente
void agregarcliente(cliente* Clnuevo)
{
	if (Clinicio == nullptr) {
		Clinicio = new cliente;
		Claux = Clinicio;
		strcpy_s(Claux->Clnombre, Clnuevo->Clnombre);
		strcpy_s(Claux->telefono, Clnuevo->telefono);
		strcpy_s(Claux->correo, Clnuevo->correo);
		strcpy_s(Claux->Clalias, Clnuevo->Clalias);
		strcpy_s(Claux->Clcomercio, Clnuevo->Clcomercio);
		Claux->nunero = 0;
		Claux->numero = 1;


		Claux->Clant = nullptr;
		Claux->Clsig = nullptr;

	}
	else {
		while (Claux->Clsig != nullptr) {
			Claux = Claux->Clsig;
		}
		Claux->Clsig = new cliente;
		Claux->Clsig->Clant = Claux;
		Claux = Claux->Clsig;
		Claux->Clsig = nullptr;

		strcpy_s(Claux->Clnombre, Clnuevo->Clnombre);
		strcpy_s(Claux->telefono, Clnuevo->telefono);
		strcpy_s(Claux->correo, Clnuevo->correo);
		strcpy_s(Claux->Clalias, Clnuevo->Clalias);
		strcpy_s(Claux->Clcomercio, Clnuevo->Clcomercio);
		Claux->nunero = 0;
		Claux->numero = 1;




	}
}

void modificarCl(cliente* newInfo, char nomUsuario[50])
{
	Claux = Clinicio;
	//char newNom[50];

	if (Claux == nullptr)
	{
		MessageBox(0, "No hay Usuario registrados", "AVISO", MB_OK | MB_ICONINFORMATION);
	}
	else {
		while (Claux != nullptr && strcmp(Claux->Clnombre, nomUsuario) != 0) {
			Claux = Claux->Clsig;
		}
		if (Claux == nullptr) {
			MessageBox(0, "Usuario no encontrado", "AVISO", MB_OK | MB_ICONINFORMATION);
		}
		else {
			strcpy_s(Claux->Clnombre, newInfo->Clnombre);
			strcpy_s(Claux->telefono, newInfo->telefono);
			strcpy_s(Claux->correo, newInfo->correo);
			strcpy_s(Claux->Clalias, newInfo->Clalias);

			MessageBox(0, "Usuario modificado", "AVISO", MB_OK | MB_ICONINFORMATION);

		}
	}
}



void eliminarCl(char nomUsu[50])
{
	Claux = Clinicio;

	if (Claux == nullptr)
	{
		MessageBox(0, "La lista esta vacia. Agregue Usuario", "AVISO", MB_OK);
	}
	else {
		while (Claux != nullptr && strcmp(Claux->Clnombre, nomUsu) != 0) { //Nos movemos en el arreglo para buscar la cancion

			Claux = Claux->Clsig;
		}
		if (Claux == nullptr) {
			MessageBox(0, "No encontrado", "AVISO", MB_OK);
		}
		else if (Claux == Clinicio) {	//El nodo es el primero 

			if (Claux->Clsig == nullptr) { //Si es el primero y unico nodo
				//delete Claux;		//Eliminamos el primer nodo
				//Clinicio = nullptr;
				//Claux = Clinicio;

				Clinicio = nullptr;
				delete Claux;
				Claux = Clinicio;
			}
			else { //Si es el primero y hay mas nodos

				//inicio = Claux->Clsig;	//Cambiamos el puntero 'inicio' al segundo nodo, que ahora es nuestro primer elemento
				//delete Claux;			//Eliminamos el primer nodo		
				//Claux = Clinicio;			//Para que Claux no quede sin apuntar a nada, la apuntamos al inicio
				//Claux->Clant = nullptr;

				Clinicio = Clinicio->Clsig;
				Claux->Clsig->Clant = nullptr;
				delete Claux;
				Claux = Clinicio;

			}

			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK);
		}
		else {

			if (Claux->Clsig == nullptr) { //Si el nodo es el �ltimo
				Claux->Clant->Clsig = nullptr;	//Clantes de eliminar, el penultumo nodo, su puntero Clsiguiente, lo igualamos a nullptr
				delete Claux;
				Claux = Clinicio;
			}
			else { //Si es cualquier nodo que no sea el inicio o el �ltimo
				Claux->Clsig->Clant = Claux->Clant;
				Claux->Clant->Clsig = Claux->Clsig;
				delete Claux;
				Claux = Clinicio; //Para que Claux no quede sin apuntar a nada, la apuntamos al inicio
			}

			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK);

		}
	}

}



void ecribircliente() {
	Claux = Clinicio;

	ofstream usuarios;
	usuarios.open("ARCHIVOESTESI", ios::out | ios::binary | ios::trunc);

	if (usuarios.is_open()) {
		if (Claux == Clinicio) {
			while (Claux != nullptr)
			{
				usuarios.write((char*)Claux, sizeof(cliente));
				Claux = Claux->Clsig;

			}
		}

	}
	usuarios.close();
}


void leercliente() {
	ifstream leerusu;
	leerusu.open("ARCHIVOESTESI", ios::in | ios::binary);

	Claux = Clinicio;
	if (leerusu.is_open()) {

		cliente* usuLeido = new cliente;


		if (Claux == Clinicio) {
			while (!leerusu.read((char*)usuLeido, sizeof(cliente)).eof()) {

				while (Claux != nullptr && Claux->Clsig != nullptr)
				{
					Claux = Claux->Clsig;
				}
				if (Claux == nullptr) {
					Clinicio = usuLeido;
					Clinicio->Clsig = nullptr;
					Clinicio->Clant = nullptr;
					Claux = Clinicio;
				}
				else {
					Claux->Clsig = usuLeido;
					Claux->Clsig->Clant = Claux;
					Claux = Claux->Clsig;
					Claux->Clsig = nullptr;
				}

				usuLeido = new cliente;
			}
		}

	}
}
//PROMOCIONES
void ventanapromo(promociones* acic)
{
	/*
int* proactive;
int* proinactive;
int* numcl;
int* consutotal;
float* totalcompras; */

	proaux = proinicio;
	//char newNom[50];

	if (proaux == nullptr)
	{
		MessageBox(0, "No hay Usuario registrados", "AVISO", MB_OK | MB_ICONINFORMATION);
	}
	else {
		while (proaux != nullptr) {
			if (strcmp(promiinfo->Clcomercio, proaux->Clcomercio) == 0) {
				if (proaux->estatus == 0) {
					int a = 0;
					proactive = &a;
					a = a + 1;
				}
				else if (proaux->estatus == 1) {
					int b = 0;
					b = b + 1;
					proinactive = &b;
				}

			}
			proaux = proaux->prosig;
		}

	}
}

void validacion(admin* valido) {


	char nombre[50] = { 0 };
	char nomaux = { 0 };
	int x = 0;

	strcpy_s(nombre, valido->nombre);

	for (x; x < sizeof(nombre); x++)
	{
		nomaux = nombre[x];

		if (isalpha(nomaux) == 0)
		{
			MessageBox(0, "Ingrese solo  carcateres alfabeticos", "AVISO", MB_OK || MB_ICONERROR);

		}
	}

	char nombrecompleto[50] = { 0 };
	char nombrecompletoaux = { 0 };
	int i = 0;

	strcpy_s(nombre, valido->nombreCompleto);

	for (i; i < sizeof(nombre); i++)
	{
		nomaux = nombre[i];

		if (isalpha(nombrecompletoaux) == 0)
		{
			MessageBox(0, "Ingrese solo  carcateres alfabeticos", "AVISO", MB_OK || MB_ICONERROR);

		}
	}

	char pass[50] = { 0 };
	char passaux = { 0 };
	int y = 0;

	strcpy_s(pass, valido->pass);

	for (y; y < sizeof(pass); y++)
	{
		passaux = pass[y];

		if (isalpha(passaux) != 0)
		{
			MessageBox(0, "Ingrese comom minimo una letra, un numero y un caracter especial", "AVISO", MB_OK || MB_ICONERROR);

		}

	}




}

void validacionC(contador* valido) {
	char nombre[50] = { 0 };
	char nomaux = { 0 };
	int x = 0;

	strcpy_s(nombre, valido->Cnombre);

	for (x; x < sizeof(nombre); x++)
	{
		nomaux = nombre[x];

		if (isalpha(nomaux) == 0)
		{
			MessageBox(0, "Ingrese solo  carcateres alfabeticos", "AVISO", MB_OK || MB_ICONERROR);

		}
	}

	char nombrecompleto[50] = { 0 };
	char nombrecompletoaux = { 0 };
	int i = 0;

	strcpy_s(nombre, valido->CnombreCompleto);

	for (i; i < sizeof(nombre); i++)
	{
		nomaux = nombre[i];

		if (isalpha(nombrecompletoaux) == 0)
		{
			MessageBox(0, "Ingrese solo  carcateres alfabeticos", "AVISO", MB_OK || MB_ICONERROR);

		}
	}

	char pass[50] = { 0 };
	char passaux = { 0 };
	int y = 0;

	strcpy_s(pass, valido->Cpass);

	for (y; y < sizeof(pass); y++)
	{
		passaux = pass[y];

		if (isalpha(passaux) != 0)
		{
			MessageBox(0, "Ingrese comom minimo una letra, un numero y un caracter especial", "AVISO", MB_OK || MB_ICONERROR);

		}

	}
}

LRESULT Email_check(string email)
{
	const regex pattern("(\\w+)(\\.|_)?(\\w*)(\\w+)(\\.(\\w+))+");
	return regex_match(email, pattern);
}

void validacioncliente(cliente* valido) {
	string Email;
	char correo[50] = { 0 };
	//cout << "\t\t\t Email Validation\n";
	strcpy_s(correo, valido->correo);
	//cout << "Enter Your Email ID: ";
	Email = correo;
	if (Email_check(Email))
	{
		MessageBox(0, "Campos correctos", "AVISO", MB_OK || MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(0, "Correo no correcto", "AVISO", MB_OK || MB_ICONERROR);
		MessageBox(0, "Ingrese con el siguuiente formato: usuario@gmail.com", "AVISO", MB_OK || MB_ICONINFORMATION);

	}

	char telefono[50] = { 0 };
	char telaux = { 0 };
	int j = 0;

	strcpy_s(telefono, valido->telefono);

	for (j; j < sizeof(telefono); j++)
	{
		telaux = telefono[j];

		if (isalpha(telaux) != 0)
		{
			MessageBox(0, "Ingrese solo carcateres numericos", "AVISO", MB_OK || MB_ICONERROR);

		}
	}

	char nombre[50] = { 0 };
	char nomaux = { 0 };
	int x = 0;

	strcpy_s(nombre, valido->Clnombre);

	for (x; x < sizeof(nombre); x++)
	{
		nomaux = nombre[x];

		if (isalpha(nomaux) == 0)
		{
			MessageBox(0, "Ingrese solo  carcateres alfabeticos", "AVISO", MB_OK || MB_ICONERROR);

		}
	}
}

//Promociones 
void agregarpromo(promociones* agregar) {
	if (proinicio == nullptr) {
		proinicio = new promociones;
		proaux = proinicio;

		strcpy_s(proaux->pronombre, agregar->pronombre);
		strcpy_s(proaux->Clcomercio, agregar->Clcomercio);
		proaux->pmonto = agregar->pmonto;
		proaux->porcentajedes = agregar->porcentajedes;
		proaux->estatus = agregar->estatus;

		proaux->proant = nullptr;
		proaux->prosig = nullptr;

	}
	else {
		while (proaux->prosig != nullptr) {
			proaux = proaux->prosig;
		}
		proaux->prosig = new promociones;
		proaux->prosig->proant = proaux;
		proaux = proaux->prosig;
		proaux->prosig = nullptr;

		strcpy_s(proaux->pronombre, agregar->pronombre);
		strcpy_s(proaux->Clcomercio, agregar->Clcomercio);
		proaux->pmonto = agregar->pmonto;
		proaux->porcentajedes = agregar->porcentajedes;
		proaux->estatus = agregar->estatus;


	}
}

void modificarpromocion(promociones* newInfo, char pronombre[50]) {
	proaux = proinicio;
	//char newNom[50];

	if (proaux == nullptr)
	{
		MessageBox(0, "No hay Usuario registrados", "AVISO", MB_OK || MB_ICONINFORMATION);
	}
	else {
		while (proaux != nullptr && strcmp(proaux->pronombre, pronombre) != 0) {
			proaux = proaux->prosig;
		}
		if (proaux == nullptr) {
			MessageBox(0, "Usuario no encontrado", "AVISO", MB_OK | MB_ICONINFORMATION);
		}
		else {
			strcpy_s(proaux->pronombre, newInfo->pronombre);
			strcpy_s(proaux->Clcomercio, newInfo->Clcomercio);
			proaux->pmonto = newInfo->pmonto;
			proaux->porcentajedes = newInfo->porcentajedes;
			proaux->estatus = newInfo->estatus;

			MessageBox(0, "Usuario modificado", "AVISO", MB_OK || MB_ICONINFORMATION);

		}
	}
}


void eliminarpromo(char nompromocion[50]) {
	proaux = proinicio;

	if (proaux == nullptr)
	{
		MessageBox(0, "La lista esta vacia. Agregue Usuario", "AVISO", MB_OK);
	}
	else {
		while (proaux != nullptr && strcmp(proaux->pronombre, nompromocion) != 0) { //Nos movemos en el arreglo para buscar la cancion

			proaux = proaux->prosig;
		}
		if (proaux == nullptr) {
			MessageBox(0, "No encontrado", "AVISO", MB_OK);
		}
		else if (proaux == proinicio) {	//El nodo es el primero 

			if (proaux->prosig == nullptr) { //Si es el primero y unico nodo
				//delete proaux;		//Eliminamos el primer nodo
				//proinicio = nullptr;
				//proaux = proinicio;

				proinicio = nullptr;
				delete proaux;
				proaux = proinicio;
			}
			else { //Si es el primero y hay mas nodos

				//inicio = proaux->prosig;	//Cambiamos el puntero 'inicio' al segundo nodo, que ahora es nuestro primer elemento
				//delete proaux;			//Eliminamos el primer nodo		
				//proaux = proinicio;			//Para que proaux no quede sin apuntar a nada, la apuntamos al inicio
				//proaux->proant = nullptr;

				proinicio = proinicio->prosig;
				proaux->prosig->proant = nullptr;
				delete proaux;
				proaux = proinicio;

			}

			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK);
		}
		else {

			if (proaux->prosig == nullptr) { //Si el nodo es el �ltimo
				proaux->proant->prosig = nullptr;	//proantes de eliminar, el penultumo nodo, su puntero prosiguiente, lo igualamos a nullptr
				delete proaux;
				proaux = proinicio;
			}
			else { //Si es cualquier nodo que no sea el inicio o el �ltimo
				proaux->prosig->proant = proaux->proant;
				proaux->proant->prosig = proaux->prosig;
				delete proaux;
				proaux = proinicio; //Para que proaux no quede sin apuntar a nada, la apuntamos al inicio
			}

			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK || MB_ICONINFORMATION);

		}
	}
}

void escribirpromo() {
	proaux = proinicio;

	ofstream usuarios;
	usuarios.open("ARCHIVOESTESI", ios::out | ios::binary | ios::trunc);

	if (usuarios.is_open()) {
		if (proaux == proinicio) {
			while (proaux != nullptr)
			{
				usuarios.write((char*)proaux, sizeof(admin));
				proaux = proaux->prosig;

			}
		}

	}
	usuarios.close();
}

void leerpromo() {
	ifstream leerusu;
	leerusu.open("ARCHIVOESTESI", ios::in | ios::binary);

	proaux = proinicio;
	if (leerusu.is_open()) {

		promociones* usuLeido = new promociones;


		if (proaux == proinicio) {
			while (!leerusu.read((char*)usuLeido, sizeof(promociones)).eof()) {

				while (proaux != nullptr && proaux->prosig != nullptr)
				{
					proaux = proaux->prosig;
				}
				if (proaux == nullptr) {
					proinicio = usuLeido;
					proinicio->prosig = nullptr;
					proinicio->proant = nullptr;
					proaux = proinicio;
				}
				else {
					proaux->prosig = usuLeido;
					proaux->prosig->proant = proaux;
					proaux = proaux->prosig;
					proaux->prosig = nullptr;
				}

				usuLeido = new promociones;
			}
		}

	}
}

//Consumos 


void agregarconsumos(compras* agregarcom) {
	if (comincio == nullptr) {
		comincio = new compras;
		coaux = comincio;
		strcpy_s(coaux->cliente, agregarcom->cliente);
		strcpy_s(coaux->Comcomercio, agregarcom->Comcomercio);
		strcpy_s(coaux->fecha, agregarcom->fecha);
		strcpy_s(coaux->fechaexacta, agregarcom->fechaexacta);
		strcpy_s(coaux->fechaultima, agregarcom->fechaultima);

		coaux->monto = agregarcom->monto;
		coaux->descuento = agregarcom->descuento;
		coaux->subtotal = agregarcom->subtotal;
		coaux->total = agregarcom->total;
		coaux->comrpastotal = 1;


		coaux->coant = nullptr;
		coaux->cosig = nullptr;

	}
	else {
		while (coaux->cosig != nullptr) {
			coaux = coaux->cosig;
		}
		coaux->cosig = new compras;
		coaux->cosig->coant = coaux;
		coaux = coaux->cosig;
		coaux->cosig = nullptr;

		strcpy_s(coaux->cliente, agregarcom->cliente);
		strcpy_s(coaux->Comcomercio, agregarcom->Comcomercio);
		strcpy_s(coaux->fecha, agregarcom->fecha);
		strcpy_s(coaux->fechaexacta, agregarcom->fechaexacta);
		strcpy_s(coaux->fechaultima, agregarcom->fechaultima);

		coaux->monto = agregarcom->monto;
		coaux->descuento = agregarcom->descuento;
		coaux->subtotal = agregarcom->subtotal;
		coaux->total = agregarcom->total;
		coaux->comrpastotal = 1;
	}
}

void modificartotalconsumo(char cliente[50], int montototal) {
	coaux = comincio;
	//char newNom[50];

	if (coaux == nullptr)
	{
		MessageBox(0, "No hay Usuario registrados", "AVISO", MB_OK || MB_ICONINFORMATION);
	}
	else {
		while (coaux != nullptr) {
			if (strcmp(coaux->cliente, cliente) == 0) {

				montototal = montototal + coaux->comrpastotal;
				coaux = coaux->cosig;
			}
			else {
				coaux = coaux->cosig;
			}
		}

	}

	montoTotal = &montototal;

}


void ventanaconsumo(compras* acic)
{

	int a = 0;
	float b = 0;
	coaux = comincio;


	if (coaux == nullptr)
	{
		MessageBox(0, "No hay Usuario registrados", "AVISO", MB_OK | MB_ICONINFORMATION);
	}
	else {
		while (coaux != nullptr) {
			if (strcmp(miInfo->comercio, coaux->Comcomercio) == 0) {

				a = a + 1;

				if (coaux->total != 0) {

					b = coaux->total + b;
					totalcompras = &b;
				}
			}
			coaux = coaux->cosig;
		}
		consutotal = &a;
	}


}

void escribirconsumos() {
	coaux = comincio;

	ofstream usuarios;
	usuarios.open("ARCHIVOESTESI", ios::out | ios::binary | ios::trunc);

	if (usuarios.is_open()) {
		if (coaux == comincio) {
			while (coaux != nullptr)
			{
				usuarios.write((char*)coaux, sizeof(admin));
				coaux = coaux->cosig;

			}
		}

	}
	usuarios.close();
}

void leerconsumos() {
	ifstream leerusu;
	leerusu.open("ARCHIVOESTESI", ios::in | ios::binary);

	coaux = comincio;
	if (leerusu.is_open()) {

		compras* usuLeido = new compras;


		if (coaux == comincio) {
			while (!leerusu.read((char*)usuLeido, sizeof(compras)).eof()) {

				while (coaux != nullptr && coaux->cosig != nullptr)
				{
					coaux = coaux->cosig;
				}
				if (coaux == nullptr) {
					comincio = usuLeido;
					comincio->cosig = nullptr;
					comincio->coant = nullptr;
					coaux = comincio;
				}
				else {
					coaux->cosig = usuLeido;
					coaux->cosig->coant = coaux;
					coaux = coaux->cosig;
					coaux->cosig = nullptr;
				}

				usuLeido = new compras;
			}
		}

	}
}

