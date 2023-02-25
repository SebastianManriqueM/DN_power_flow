#pragma once

# include <stdio.h>
# include <conio.h>
# include <math.h>
# include <string.h>
# include <stdlib.h>
# include <complex>
# include <iostream>
# include <vector>
# include <list>
# include <time.h>
# include <algorithm> 
# include <cstdlib>
# include <omp.h>
# include <fstream>
# include <time.h>

using namespace std;


class Calculo_do_fluxo
{
public:
	Calculo_do_fluxo  (void);
	~Calculo_do_fluxo (void);

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Declaração das funções
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	void  leitura_dados                            (char nome_sistema [100]);
	void  alocacao_memoria                         (int Numero_barras, int Numero_linhas);
	void  ordenamento_barras                       (int * Ni, int * Nj, int * Ramo, int Numero_linhas);
	void  renumaracao_barras                       (int * Ni, int * Nj, int * Ramo, int Numero_linhas, int * IndexRamo, int * Ni_ord, int * Nj_ord);
	void  deletar_memoria                          (int Numero_barras, int Numero_linhas);
	void  fluxo_potencia_mono                      ();
	void  fluxo_potencia_tri                       ();
	void  curto_circuito                           ();
	void  alocacao_elos_fusiveis_trafos            ();
	void  dimensionamento_tcs                      ();
	void  coordenação_reles                        ();
	void  seletividade_elos_fusiveis_k             ();
    void  encontrar_pais_e_filhos                  ();
		 
	void  curvas_fusiveis                          (int maior_fusivel, int intervalo, int curva_fusao_interrupcao);
	void  alocacao_elos_fusiveis_trafos_novo       (int indice);
	void  alocacao_elos_fusiveis_retaguarda_trafos (int indice);
	void  verifica_amperagem_fusivel               (int indice);
	void  coordenacao_entre_elos_fusiveis          (int indice);
	void  seletividade_elos_fusiveis_k_novo        ();
	void  impressao_seletividade                   (char nome_sistema [100]);
	float T_rele                                   (int Tipo_Norma, int Tipo_Curva, float M_rele, float Dial);
	float Dial_rele                                (int Tipo_Norma, int Tipo_Curva, float M_rele, float T_procurado);

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Declaração de variáveis
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	int                Tipo_sistema;   // Monofásico(1), Trifásico(3)
	int                Numero_barras; 
	int                Numero_linhas;
	double             I_base;
	double             V_base;         // kV base
	double             V_ref;		   // kV ref (pode ter regulador de tensão)
	int                Uni_linhas;     // (m, km, ft, milhas)
	int                Uni_imp;        // (ohm,ohm/m,ohm/km,ohm/ft,ohm/milha)
	int                Uni_demanda;    // (VAR,kVAR, MVA)
	double             S_sub;		   // kVA sub
	double             V_alta_sub;     // kV no lado da alta tensão
	double             V_baixa_sub;    // kV
	double             R1_sub;
	double             X1_sub;
	complex <double>   Z1_sub;
	complex <double>   Z0_sub;
	double             R0_sub;
	double             X0_sub;
	int              * Barras;
	int              * Tipo_barras;
	complex <double> * Sa;
	complex <double> * Sb;
	complex <double> * Sc;
	complex <double> * Ca;
	complex <double> * Cb;
	complex <double> * Cc;
	int				 * Modelo_carga;
	double             Uni_demanda_real;
	double             S_base;
	double             Z_base;
	complex <double> * Zaa;
	complex <double> * Zbb;
	complex <double> * Zcc;
	complex <double> * Zab;
	complex <double> * Zbc;
	complex <double> * Zac;
	complex <double> * Zan;
	complex <double> * Zbn;
	complex <double> * Zcn;
	complex <double> * Znn;
	int              * Ni;
	int              * Nj;
	vector  <string>   Tipo_Circuito;
	vector  <string>   Tipo_Cabo;
	double           * Comprimento;
	double             Unidade_real_imp;
	int              * Ramo;
	int              * IndexRamo;
    int              * BarrasProcessadas;
	int              * Nj_ord;
	int              * Ni_ord;
	int              * Apontador;
	int              * Index;
	int              * Ni_renum;
	int              * Nj_renum;
	int              * Norma_curva; // 1 -  IEC/ABNT; 2 - IAC (GE); 3 - US; 4 - ANSI/IEEE
	int              * Tipo_curva;  // se IEC/ABNT ou IAC (GE): 1 - Inversa;       2 - Muito Inversa;        3 - Extremamente Inversa; 4 - Pouco Inversa
								    // se US:                   1 - Inversa;       2 - Muito Inversa;        3 - Extremamente Inversa; 4 - Pouco Inversa; 5 - Moderadamente Inversa
									// se ANSI/IEEE:            1 - Muito Inversa; 2 - Extremamente Inversa; 3 - Moderadamente Inversa
	int              * Barras_renum;
	complex <double> * Ia_nodal;
	complex <double> * Ia_linha;
	complex <double> * Ia_nodal_aux;
	complex <double> * Va_barra;
	complex <double> * Ib_nodal;
	complex <double> * Ib_linha;
	complex <double> * Vb_barra;
	complex <double> * Ic_nodal;
	complex <double> * Ic_linha;
	complex <double> * Vc_barra;
	int                BarraSub;
	complex <double> * Delta_Sa;
	complex <double> * Delta_Sb;
	complex <double> * Delta_Sc;
	double             Convergencia;
	int                Convergiu;
	int              * IndexBarra;
    double             Perdas;
	int                i, j, k, i1, i2, i3, j1, j2, j3, k1, k2, k3;
	int                aux;
	int                aux2;
	int                barra_trocada;
	complex <double>   Angle_120;
	complex <double>   Angle_240;
	int              * Linha_A;
	int              * Linha_B;
	int              * Linha_C;
	complex <double> * Z1;
	complex <double> * Z0;
	complex <double> * Z1_eq;
	complex <double> * Z0_eq;
	double           * Icc_3ph;
	double           * Icc_2ph;
	double           * Icc_1ph;
	double           * Icc_3ph_As;
	double           * Icc_2ph_As;
	double           * Icc_1ph_As;
	double           * Icc_1ph_min;
	double           * R;
	double           * X;
	double           * X_Barra_R;
	double           * X_Barra_R_zero;
	double           * Icc_max;
	float              K;
	double           * Ia_carga;
	double           * I_carga;
	double           * Ib_carga;
	double           * Ic_carga;
	double           * I_carga_max;
	int              * Tipo_CH;
	int              * IndexStruct;
	int              * IndexStructTudo;
	string             Elo_Preferencial;
	double           * I_coord;
	double           * I_inrush;
	int                elo;
	float              V_aux;
	double             Aux_I_elo;
	int                ValorElo, ValorElo_Protetor_K, Ramo_Fusivel_Protetor, pai, filho;
	string             TipoElo_Protetor,Fusivel_Protegido_K; // Proteção primaria e retaguarda
	double             I_coord_filho;
	int                Quantidade_de_DJ;
	float            * Vetor_B;
	int              * Vetor_Beq;
	int              * F_O;
	int              * IndexStructCH;
	int              * IndexStructDJ;
	float            * Icc_analisados;
	float            * TDS_analisados;
	float            * T_rele_analisados;
	float            * T_fusivel_analisados;
	float              a_rele;
	float              b_rele;
	float              c_rele;
	float              d_rele;
	float              e_rele;
	float              p_rele;
	float              n_rele;
	int                tipo_curva;
    float            * T_fusivel;
	float            * T_fusivel_neutro;
	float            * Delta_T_protecao_retaguarda_primaria;
	float            * T_protecao_retaguarda;    
	float            * T_protecao_primaria;
	string             Tipo_curva_string;
	float              Intervalo_Coord_rele_fusivel;       
	float              Intervalo_Coord_rele_rele;          
	float              Intervalo_Coord_rele_religador;    
	float              Intervalo_Coord_religador_religador;
	float              Intervalo_Coord_religador_fusivel;
	float            * Icc_analisados_neutro;                       
	float            * TDS_analisados_neutro;                       
	float            * T_protecao_retaguarda_neutro;                
	float            * T_protecao_primaria_neutro;                  
	float            * Delta_T_protecao_retaguarda_primaria_neutro;
	float              aux_Icc_min;
	float              aux_Icc_min_neutro;
	float              aux_Icc_min_aux;
	float              aux_Icc_min_neutro_aux;
	int                norma_curva;
	float              aux_Ipartida;
	int                Stop;
	int                aux_icc_min_dial_min_trecho;
	int                aux_icc_max_dial_min_trecho;
	int                aux_icc_min_dial_min_trecho_neutro;
	int                aux_icc_max_dial_min_trecho_neutro;
	int                aux_menor_intervalo;
	int                aux_menor_intervalo_neutro;
	int                aux_intervalo;
	float              FI;       
	float              Delta_tap;
	float              Dial_max;
	float              Dial_min;
	float                FS;
	float                FT;
	int                Tipo_coordenacao;
	float              ZC;
	float              taxa;   
	float              anos;   
	float              Fator_K;
	float              K_religador;
	float              K_desequilibrio; 
	float              const_k;
	int                Coordenado_ou_seletivo;
	float              Tempo_rele;
	float              Dial_Rele;
	float              aux_tempo_rele;
	int                Modo_calculo_I_carga;


	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	struct Trafos_Distri{
	
	int                Ni;
	int				   Nj;
	int                Ramo_ini;
	//--------------------------------
	int                Ni_renum;
	int				   Nj_renum;
	int                Ramo_ord;
	//--------------------------------
	int                ConexTrafo;
	double			   PotenciaTrafo;
	double			   TensaoPrim;
	double             TensãoSecun;
	double             XTrafo;
	double             RTrafo;
	int				   PosiTapTrafo;
	string             IDtrafo;
	int                ValorElo;
	string             TipoElo;
	int                Struct_Pai;
	string             Tipo_Pai;

	//--------------------------------
	double              Icc1f;
	double              Icc1f_min;
	double              Icc2f_min;
	double              Icc3f;
	double              Icc_max;
	double              Icc_3f_coord;
	double              Icc_1f_coord;
	};

	vector <Trafos_Distri> TRAFOS_DISTRI; // Vetor das estruturas de Trafos de Distribuição

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	struct FilhosDJ {
	
	int                 Ramos_ord_FilhoDJ;
	int                 Pos_struct_Filho;
	string              TiposFilhosDJ;
	//--------------------------------
	int                 TipoChave;
	//int                 Posicao_na_struct;
	string              TipoEloFilhoDJ;
	int                 ValorElo;
	string              Coordenado;
	string              Coordenado_neutro;
	string              Coordenado_rapida;
	string              Coordenado_rapida_neutro;
	//--------------------------------
	};

	struct DisjuntorProt{
	
	int                Ni;
	int				   Nj;
	int                Ramo_ini;
	//--------------------------------
	int                Ni_renum;
	int				   Nj_renum;
	int                Ramo_ord;
	//--------------------------------
	double              Icc1f;
	double              Icc1f_min;
	double              Icc2f_min;
	double              Icc3f;
	double              Icc_max;
	double              Icc_1f_min_protegido;
	double              Icc_2f_min_protegido;
	double              Icc_3f_coord;
	double              Icc_1f_coord;
	double              Icc_coord_fase_min;
	double              Icc_coord_fase_max;
	double              Icc_coord_neutro_min;
	double              Icc_coord_neutro_max;
	//-------------------------------
	double             Icarga;
	double             Ipickup_fase;
	double             Ipickup_neutro;
	double             Iinrush;
	double             Iprimaria;
	double             Isecundaria;
	double             RTC;
	double             I_instantaneo;
	double             I_instantaneo_neutro;
	double             Tap_Temporizado_fase; 
	double             Tap_Instantaneo_fase;
	double             Tap_Temporizado_neutro; 
	double             Tap_Instantaneo_neutro;
	double             Dial_fase;
	double             Dial_neutro;
	int                Norma_Curva; // 1 -  IEC/ABNT; 2 - IAC (GE); 3 - US; 4 - ANSI/IEEE    
	int                Tipo_Curva;  // se IEC/ABNT ou IAC (GE): 1 - Inversa;       2 - Muito Inversa;        3 - Extremamente Inversa; 4 - Pouco Inversa
								    // se US:                   1 - Inversa;       2 - Muito Inversa;        3 - Extremamente Inversa; 4 - Pouco Inversa; 5 - Moderadamente Inversa
								    // se ANSI/IEEE:            1 - Muito Inversa; 2 - Extremamente Inversa; 3 - Moderadamente Inversa
	int                Coordenado_dial_min; // Caso o dispositivo de proteção fique coordenado com o dial mínimo, não é garantido o intervalo de coordenação mínimo
	int                Coordenado_dial_min_neutro;
	string             Tipo_Curva_string;
	string             Norma_Curva_string;
	
	vector <FilhosDJ>  STRUCTFILHOSDJ;
 	};

	vector <DisjuntorProt> DISJUNTORPROT;

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	struct FilhosCH {
	
	int                 Ramos_ord_FilhoCH;
	int                 Pos_struct_Filho;
	int                 TipoChave;
	string              TiposFilhosCH;
	int                 ValorElo;
	string              TipoEloFilhoCH;
	string              Coordenado;
	string              Coordenado_neutro;
	string              Coordenado_rapida;
	string              Coordenado_rapida_neutro;
	};

	struct ChaveProt {

	string              TipoElemento;
	int                 TipoCH; // CH_0: CH fusível, CH_1: Tripolar, CH_2: Óleo, CH_3: Unipolar, CH_4: Fusível_religador, CH_5: Magnética, CH_6: Religador
	string              CodigoCH;
	int                 Ramo_ini;
	int                 Ni;
	int                 Nj;
	int                 Ni_renum;
	int                 Nj_renum;
	int                 Ramo_ord;
	string              EloCH;
	string              Coordenado;
	int                 ValorElo;
	string              TipoElo;
	double              Icarga;
	float               RTC;
	float               Iprimaria;
	float               Isecundaria;
	double              I_instantaneo;
	double              I_instantaneo_neutro;
	//double              T_atuacao_inst;
	//double              T_atuacao_inst_neutro;
	double              Tap_Temporizado_fase; 
	double              Tap_Instantaneo_fase;
	double              Tap_Temporizado_neutro; 
	double              Tap_Instantaneo_neutro;
	double              Iinrush;
	double              Icc1f;
	double              Icc1f_min;
	double              Icc2f_min;
	double              Icc3f;
	double              Icc_max;
	double              Icc_coord_fase_min;
	double              Icc_coord_fase_max;
	double              Icc_coord_neutro_min;
	double              Icc_coord_neutro_max;
	double              Icc_3f_coord;
	double              Icc_1f_coord;
	double              Icc_1f_min_protegido;
	double              Icc_2f_min_protegido;
	double              Religador_Dial_fase_rapida;
	double              Religador_Dial_fase_retardada;
	double              Religador_Dial_neutro_rapida;
	double              Religador_Dial_neutro_retardada;
	int                 Religador_Norma_Curva; // 1 -  IEC/ABNT; 2 - IAC (GE); 3 - US; 4 - ANSI/IEEE
	int                 Religador_Tipo_Curva;  // se IEC/ABNT ou IAC (GE): 1 - Inversa;       2 - Muito Inversa;        3 - Extremamente Inversa; 4 - Pouco Inversa
											   // se US:                   1 - Inversa;       2 - Muito Inversa;        3 - Extremamente Inversa; 4 - Pouco Inversa; 5 - Moderadamente Inversa
					 						   // se ANSI/IEEE:            1 - Muito Inversa; 2 - Extremamente Inversa; 3 - Moderadamente Inversa
	string              Tipo_Curva_string;
	string              Norma_Curva_string;
	double              Religador_Ipickup_fase;
	double              Religador_Ipickup_neutro;
	string              Abertura_Rapida_Coordenada;
	string              Abertura_Rapida_Coordenada_neutro;
	int                 Coordenado_dial_min; // Caso o dispositivo de proteção fique coordenado com o dial mínimo, não é garantido o intervalo de coordenação mínimo
	int                 Coordenado_dial_min_neutro; // Caso o dispositivo de proteção fique coordenado com o dial mínimo, não é garantido o intervalo de coordenação mínimo

	//-----------------------------
	vector <FilhosCH>   STRUCTFILHOSCH;

	};

	vector <ChaveProt>  CHAVEPROT;

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	struct Reguladores {
    
	int                 Ni;
	int                 Nj;
	int                 Ni_renum;
	int                 Nj_renum;
	int                 Ramo_ini;
	int                 Barra_tensao_controlar;
	double              Tensao_controlar;
	int                 Tipo_religador;
	int                 RT_Fixo_Variavel;
	int                 Tap_A;
	int                 Tap_b;
	int                 Tap_c;
	string              ID_regulador;
	};
	
	vector <Reguladores> REGULADORES;

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	int c1;
};