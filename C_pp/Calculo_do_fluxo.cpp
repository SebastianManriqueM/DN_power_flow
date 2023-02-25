#include "StdAfx.h"
#include "Calculo_do_fluxo.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Necessário para o cálculo dos tempos computacionais
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#include <time.h>
//
//__declspec(naked)
//LONGLONG read_tsc(void)
//{
//__asm __emit 0x0F
//__asm __emit 0x31
//__asm ret
//}
//
//double get_average_cycles()
//{
//int i = 0;
//LONGLONG start, end;
//double cycles, average_cycles=0;
//
////printf("calculating...\n");
//
//for( ; i < 11; i++ ) 
//{
//
//start = read_tsc();
//Sleep(1000);
//end = read_tsc();
//cycles = (double)end-start;
//
//// first read is inaccurate, exclude it from averaging
//if( i != 0 )
//{
//average_cycles += cycles;
////printf("%.0f cycles per second\n", cycles);
//}
//}
//average_cycles /= 10.0f;
////printf("done\nCPU running at %f mhz\n", average_cycles / 1000000.0f);
//
//return average_cycles;
//}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

Calculo_do_fluxo::Calculo_do_fluxo (void)
{
}

Calculo_do_fluxo::~Calculo_do_fluxo (void)
{
}

void Calculo_do_fluxo::alocacao_memoria (int Numero_barras, int Numero_linhas)
{
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Aloca espaço na memória
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Ia_nodal    = new complex<double> [ Numero_barras ];
	Ib_nodal    = new complex<double> [ Numero_barras ];
	Ic_nodal    = new complex<double> [ Numero_barras ];
	Ia_linha    = new complex<double> [ Numero_barras ];
	Ib_linha    = new complex<double> [ Numero_barras ];
	Ic_linha    = new complex<double> [ Numero_barras ];
	Va_barra    = new complex<double> [ Numero_barras ];
	Vb_barra    = new complex<double> [ Numero_barras ];
	Vc_barra    = new complex<double> [ Numero_barras ];
	Delta_Sa    = new complex<double> [ Numero_barras ];
	Delta_Sb    = new complex<double> [ Numero_barras ];
	Delta_Sc    = new complex<double> [ Numero_barras ];
	Z0_eq       = new complex<double> [ Numero_barras ];
	Z1_eq       = new complex<double> [ Numero_barras ];
	Icc_3ph     = new double          [ Numero_barras ];
	Icc_2ph     = new double          [ Numero_barras ];
	Icc_1ph     = new double          [ Numero_barras ];
    Icc_3ph_As  = new double          [ Numero_barras ];
	Icc_2ph_As  = new double          [ Numero_barras ];
	Icc_1ph_As  = new double          [ Numero_barras ];
	Icc_1ph_min = new double          [ Numero_barras ];
	Icc_max     = new double          [ Numero_barras ];
	R           = new double          [ Numero_barras ];
	X           = new double          [ Numero_barras ];
	X_Barra_R   = new double          [ Numero_barras ];
	X_Barra_R_zero= new double          [ Numero_barras ];
	Ia_carga    = new double          [ Numero_barras ];
	Ib_carga    = new double          [ Numero_barras ];
	Ic_carga    = new double          [ Numero_barras ];
	I_carga     = new double          [ Numero_barras ];
	I_carga_max = new double          [ Numero_barras ];
	I_coord     = new double          [ Numero_barras ];
	I_inrush    = new double          [ Numero_barras ];

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Zeram as memórias
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

	memset (Va_barra    , 0, Numero_barras*sizeof(complex<double>));
	memset (Vb_barra    , 0, Numero_barras*sizeof(complex<double>));
	memset (Vc_barra    , 0, Numero_barras*sizeof(complex<double>));
	memset (Ia_linha    , 0, Numero_barras*sizeof(complex<double>));
	memset (Ib_linha    , 0, Numero_barras*sizeof(complex<double>));
	memset (Ic_linha    , 0, Numero_barras*sizeof(complex<double>));
	memset (Ia_nodal    , 0, Numero_barras*sizeof(complex<double>));
	memset (Ib_nodal    , 0, Numero_barras*sizeof(complex<double>));
	memset (Ic_nodal    , 0, Numero_barras*sizeof(complex<double>));
	memset (Delta_Sa    , 0, Numero_barras*sizeof(complex<double>));
	memset (Delta_Sb    , 0, Numero_barras*sizeof(complex<double>));
	memset (Delta_Sc    , 0, Numero_barras*sizeof(complex<double>));
	memset (Z0_eq       , 0, Numero_barras*sizeof(complex<double>));
	memset (Z1_eq       , 0, Numero_barras*sizeof(complex<double>));
	memset (Icc_3ph     , 0, Numero_barras*sizeof(double));
	memset (Icc_2ph     , 0, Numero_barras*sizeof(double));
	memset (Icc_1ph     , 0, Numero_barras*sizeof(double));
	memset (Icc_3ph_As  , 0, Numero_barras*sizeof(double));
	memset (Icc_2ph_As  , 0, Numero_barras*sizeof(double));
	memset (Icc_1ph_As  , 0, Numero_barras*sizeof(double));
	memset (Icc_1ph_min , 0, Numero_barras*sizeof(double));
	memset (Icc_max     , 0, Numero_barras*sizeof(double));
	memset (R           , 0, Numero_barras*sizeof(double));
	memset (X           , 0, Numero_barras*sizeof(double));
	memset (X_Barra_R   , 0, Numero_barras*sizeof(double));
	memset (X_Barra_R_zero, 0, Numero_barras*sizeof(double));
	memset (Ia_carga    , 0, Numero_barras*sizeof(double));
	memset (Ib_carga    , 0, Numero_barras*sizeof(double));
	memset (Ic_carga    , 0, Numero_barras*sizeof(double));
	memset (I_carga    , 0, Numero_barras*sizeof(double));
	memset (I_carga_max , 0, Numero_barras*sizeof(double));
	memset (I_coord     , 0, Numero_barras*sizeof(double));
	memset (I_inrush    , 0, Numero_barras*sizeof(double));
}

void Calculo_do_fluxo::deletar_memoria (int Numero_barras, int Numero_linhas)
{
	delete [] Ia_nodal;     
	delete [] Ia_linha;    
	delete [] Va_barra;     
	delete [] Ib_nodal;     
	delete [] Ib_linha;     
	delete [] Vb_barra;     
	delete [] Ic_nodal;     
	delete [] Ic_linha;     
	delete [] Vc_barra;     
	delete [] Delta_Sa;     
	delete [] Delta_Sb;	 
	delete [] Delta_Sc;	 
}

void Calculo_do_fluxo::leitura_dados (char nome_sistema [100]) 
{
	char Texto_lixo [100];
		
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Abrir o arquivo do sistema elétrico
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	FILE *inicio;
	if(!(inicio = fopen ( nome_sistema ,"r"))){ printf("Erro ao tentar abrir o arquivo: sistema"); getch();}

	fscanf( inicio, "%s%d%s%d%s%d%s%lf%s%lf%s%d%s%d%s%d", &Texto_lixo, &Tipo_sistema, &Texto_lixo, &Numero_barras, &Texto_lixo, &Numero_linhas, &Texto_lixo, &V_base, &Texto_lixo, &V_ref, &Texto_lixo, &Uni_linhas, &Texto_lixo, &Uni_imp, &Texto_lixo, &Uni_demanda );
	fscanf( inicio, "%s%s%s%s%s%s%s",                     &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo);
	fscanf( inicio, "%s%lf%lf%lf%lf%lf%lf%lf",            &Texto_lixo, &S_sub, &V_alta_sub, &V_baixa_sub, &R1_sub, &X1_sub, &R0_sub, &X0_sub);
	fscanf( inicio, "%s%s%s%s%s%s%s%s%s",                 &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo); 

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Valor de base
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	V_base  *= 1.0e3 / sqrt (3.0);          // Tensão monofásica
	S_base   = S_sub * 1.0e3 / 3.0;         // Potência monofásica
	V_ref   *= 1.0e3 / sqrt (3.0);          // Tensão monofásica
	I_base   = S_base / V_base;
	//V_base = V_ref / V_base;
	Z_base   = pow (V_base, 2.0) / S_base;  // V^2/Sb

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Alocação de memória para os dados das cargas
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Barras       = new int              [Numero_barras];                     
	Tipo_barras  = new int              [Numero_barras];				
	Sa           = new complex <double> [Numero_barras];			
	Sb           = new complex <double> [Numero_barras];			
	Sc           = new complex <double> [Numero_barras];			
	Ca           = new complex <double> [Numero_barras];			
	Cb           = new complex <double> [Numero_barras];			
	Cc           = new complex <double> [Numero_barras];			
	Modelo_carga = new int              [Numero_barras];				
	
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Variáveis necessárias para ler os valores complexos
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	double s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12;
	double ZaaR, ZaaI, ZbbR, ZbbI, ZccR, ZccI, ZabR, ZabI, ZacR, ZacI, ZbcR, ZbcI, ZanR, ZanI, ZbnR, ZbnI, ZcnR, ZcnI, ZnnR, ZnnI; 

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Leitura dos dados das cargas
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	if ( Uni_demanda == 1 )
	{
		Uni_demanda_real = 1.0;
	}

	else if ( Uni_demanda == 2 )
	{
		Uni_demanda_real = 1.0E3;
	}

	else if ( Uni_demanda == 3)
	{
		Uni_demanda_real = 1.0E6;
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	for ( i = 0; i < Numero_barras; ++i ) 
	{
		fscanf ( inicio, "%d%d%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%d", &Barras[i], &Tipo_barras[i], &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8, &s9, &s10, &s11, &s12, &Modelo_carga[i] );
		
		Sa[i].real (s1  * Uni_demanda_real/S_base);    Sa[i].imag (s2  * Uni_demanda_real/S_base);
		Sb[i].real (s3  * Uni_demanda_real/S_base);    Sb[i].imag (s4  * Uni_demanda_real/S_base);
		Sc[i].real (s5  * Uni_demanda_real/S_base);    Sc[i].imag (s6  * Uni_demanda_real/S_base);			
		Ca[i].real (s7  * Uni_demanda_real/S_base);    Ca[i].imag (s8  * Uni_demanda_real/S_base);
		Cb[i].real (s9  * Uni_demanda_real/S_base);    Cb[i].imag (s10 * Uni_demanda_real/S_base);
		Cc[i].real (s11 * Uni_demanda_real/S_base);    Cc[i].imag (s12 * Uni_demanda_real/S_base);
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Alocação de memoria para as variaveis dos dados dos cabos
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Zaa         = new complex<double>    [ Numero_linhas ];
	Zbb         = new complex<double>	 [ Numero_linhas ];
	Zcc         = new complex<double>	 [ Numero_linhas ];
	Zab         = new complex<double>	 [ Numero_linhas ];
	Zac         = new complex<double>	 [ Numero_linhas ];
	Zbc         = new complex<double>	 [ Numero_linhas ];
	Zan         = new complex<double>	 [ Numero_linhas ];
	Zbn         = new complex<double>	 [ Numero_linhas ];
	Zcn         = new complex<double>	 [ Numero_linhas ];
	Znn         = new complex<double>	 [ Numero_linhas ];
	Z1          = new complex<double>	 [ Numero_linhas ];
	Z0          = new complex<double>	 [ Numero_linhas ]; 
    Ni          = new int                [ Numero_linhas ];
	Nj          = new int                [ Numero_linhas ];
	Comprimento = new double             [ Numero_linhas ];
	Ramo        = new int                [ Numero_linhas ]; 
	Tipo_CH     = new int                [ Numero_linhas ]; 
	Norma_curva = new int                [ Numero_linhas ];
	Tipo_curva  = new int                [ Numero_linhas ];

	memset (Zaa        , 0, Numero_linhas*sizeof(complex<double>));
	memset (Zbb        , 0, Numero_linhas*sizeof(complex<double>));
	memset (Zcc        , 0, Numero_linhas*sizeof(complex<double>));
	memset (Zab        , 0, Numero_linhas*sizeof(complex<double>));
	memset (Zac        , 0, Numero_linhas*sizeof(complex<double>));
	memset (Zbc        , 0, Numero_linhas*sizeof(complex<double>));
	memset (Zan        , 0, Numero_linhas*sizeof(complex<double>));
	memset (Zbn        , 0, Numero_linhas*sizeof(complex<double>));
	memset (Zcn        , 0, Numero_linhas*sizeof(complex<double>));
	memset (Znn        , 0, Numero_linhas*sizeof(complex<double>));
	memset (Comprimento, 0, Numero_linhas*sizeof(double));
	memset (Norma_curva, 0, Numero_linhas*sizeof(int));
	memset (Tipo_curva , 0, Numero_linhas*sizeof(int));
	//memset (Tipo_CH    , 0, Numero_linhas*sizeof(int));

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Desnormalizar dados da linha
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	if (Uni_imp == 1 && Uni_linhas == 1) { Unidade_real_imp = 1.0;    };	
	if (Uni_imp == 2 && Uni_linhas == 1) { Unidade_real_imp = 1.0;    };	
	if (Uni_imp == 2 && Uni_linhas == 2) { Unidade_real_imp = 1000.0; };
	if (Uni_imp == 3 && Uni_linhas == 1) { Unidade_real_imp = 1.0e-3; };	
	if (Uni_imp == 3 && Uni_linhas == 2) { Unidade_real_imp = 1.0;    };
	if (Uni_imp == 4 && Uni_linhas == 1) { Unidade_real_imp = 3.2780; };	
	if (Uni_imp == 4 && Uni_linhas == 2) { Unidade_real_imp = 3278.0; };
	if (Uni_imp == 5 && Uni_linhas == 1) { Unidade_real_imp = 6.21e-5;};	
	if (Uni_imp == 5 && Uni_linhas == 2) { Unidade_real_imp = 6.21e-2;};
	if (Uni_imp == 5 && Uni_linhas == 3) { Unidade_real_imp = 1.89e-4;};

	// ARRUMAR DEPOIS
	
	fscanf( inicio,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo, &Texto_lixo);

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Trafos_Distri  Trafos_Distri_temp;
	DisjuntorProt  DisjuntorProt_temp;
	ChaveProt      ChaveProt_temp;
	Reguladores    Reguladores_temp;
	 
	int     ConexTrafo_aux;
	double	PotenciaTrafo_aux;
	double	TensaoPrim_aux;
	double  TensãoSecun_aux;
	double  XTrafo_aux;
	double  RTrafo_aux;
	int		PosiTapTrafo_aux;
    char    IDtrafo_aux       [100];
	int     TipoCH_aux; // CH_0: CH fusível, CH_1: Tripolar, CH_2: Óleo, CH_3: Unipolar, CH_4: Fusível_religador, CH_5: Magnética, CH_6: Religador
	char    CodigoCH_aux      [100];
	char    Tipo_circuito_aux [100];
	char    Tipo_cabo_aux     [100];
	int     Barra_tensao_controlar_aux;
	double  Tensao_controlar_aux;
	int     Tipo_religador_aux;
	int     RT_Fixo_Variavel_aux;
	int     Tap_A_aux;
	int     Tap_b_aux;
	int     Tap_c_aux;
	char    ID_regulador_aux  [100];
	
		for ( i = 0; i < Numero_linhas; ++i) 
		{
			fscanf (inicio,"%s", &Tipo_circuito_aux);
			Ramo [i] = i;
			Zaa  [i] = 0;
			Zbb  [i] = 0;
			Zcc  [i] = 0;
			Zab  [i] = 0;
			Zac  [i] = 0;
			Zbc  [i] = 0;
			Zan  [i] = 0;
			Zbn  [i] = 0;
			Zcn  [i] = 0;
			Znn  [i] = 0;

           if( strcmp (Tipo_circuito_aux, "DJ" ) == 0)
		   {
			    fscanf (inicio,"%d %d %d %d", 
					    &Ni[i], &Nj[i], &Norma_curva [i], &Tipo_curva [i] );

				Tipo_Circuito.push_back ( Tipo_circuito_aux );
				Tipo_Cabo.push_back     ( ""                );

				DisjuntorProt_temp.Ni          = Ni [i];
				DisjuntorProt_temp.Nj          = Nj [i];
				DisjuntorProt_temp.Ramo_ini    = i;
				DisjuntorProt_temp.Norma_Curva = Norma_curva [i];
				DisjuntorProt_temp.Tipo_Curva  = Tipo_curva [i];

				DISJUNTORPROT.push_back (DisjuntorProt_temp);
		   }

		   else if ( strcmp (Tipo_circuito_aux, "TR" ) == 0)
		   {
			    fscanf (inicio,"%d %d %s %d %lf %lf %lf %lf %lf %d ", 
					    &Ni[i], &Nj[i], &IDtrafo_aux, &ConexTrafo_aux, &PotenciaTrafo_aux, &TensaoPrim_aux, &TensãoSecun_aux, &XTrafo_aux, &RTrafo_aux, &PosiTapTrafo_aux);

				Tipo_Circuito.push_back ( Tipo_circuito_aux );
				Tipo_Cabo.push_back     ( ""                );
				Trafos_Distri_temp.Ni            = Ni [i];
				Trafos_Distri_temp.Nj            = Nj [i];
				Trafos_Distri_temp.Ramo_ini      = i;
				Trafos_Distri_temp.IDtrafo       = IDtrafo_aux;
				Trafos_Distri_temp.ConexTrafo    = ConexTrafo_aux;
				Trafos_Distri_temp.PotenciaTrafo = PotenciaTrafo_aux;
				Trafos_Distri_temp.TensaoPrim    = TensaoPrim_aux;
				Trafos_Distri_temp.TensãoSecun   = TensãoSecun_aux;
				Trafos_Distri_temp.XTrafo        = XTrafo_aux;
				Trafos_Distri_temp.RTrafo        = RTrafo_aux;
				Trafos_Distri_temp.PosiTapTrafo  = PosiTapTrafo_aux;

				TRAFOS_DISTRI.push_back (Trafos_Distri_temp);
		   }

		   else if( strcmp (Tipo_circuito_aux, "CH" ) == 0)
		   {
			    fscanf (inicio,"%d %d %s %d", &Ni[i], &Nj[i], &CodigoCH_aux, &TipoCH_aux);

				if (TipoCH_aux == 6)
				{
					fscanf (inicio, "%d %d", &Norma_curva[i], &Tipo_curva [i]);
					ChaveProt_temp.Religador_Norma_Curva = Norma_curva [i];
					ChaveProt_temp.Religador_Tipo_Curva  = Tipo_curva  [i];
				}

				Tipo_CH [i] = TipoCH_aux;
				Tipo_Circuito.push_back ( Tipo_circuito_aux );
				Tipo_Cabo.push_back     ( ""                );
				ChaveProt_temp.Ni       = Ni [i];
				ChaveProt_temp.Nj       = Nj [i];
				ChaveProt_temp.Ramo_ini = i;
				ChaveProt_temp.CodigoCH = CodigoCH_aux;
				ChaveProt_temp.TipoCH   = TipoCH_aux;
				 
				CHAVEPROT.push_back (ChaveProt_temp);
		   }

		   else if ( strcmp (Tipo_circuito_aux, "RT" ) == 0)
		   {

			    fscanf (inicio,"%d %d %s %d %lf %d %d %d %d %d", &Ni[i], &Nj[i], &ID_regulador_aux, &Barra_tensao_controlar_aux, &Tensao_controlar_aux, &Tipo_religador_aux,
					    &RT_Fixo_Variavel_aux, &Tap_A_aux, &Tap_b_aux, &Tap_c_aux );

				Tipo_Circuito.push_back ( Tipo_circuito_aux );
				Tipo_Cabo.push_back     ( ""                );

				Reguladores_temp.Ni                     = Ni[i];
				Reguladores_temp.Nj                     = Nj[i];
				Reguladores_temp.Ramo_ini               = i;
				Reguladores_temp.ID_regulador           = ID_regulador_aux;
				Reguladores_temp.Barra_tensao_controlar = Barra_tensao_controlar_aux;
				Reguladores_temp.Tensao_controlar       = Tensao_controlar_aux;
				Reguladores_temp.Tipo_religador         = Tipo_religador_aux;
				Reguladores_temp.RT_Fixo_Variavel       = RT_Fixo_Variavel_aux;
				Reguladores_temp.Tap_A                  = Tap_A_aux;
				Reguladores_temp.Tap_b                  = Tap_b_aux;
				Reguladores_temp.Tap_c                  = Tap_c_aux;

				REGULADORES.push_back (Reguladores_temp);	
		   }  

		   else if ( strcmp (Tipo_circuito_aux, "CP" ) == 0)
		   {
			   if (Uni_imp == 1)
				{
					fscanf (inicio,"%d %d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %s %lf", 
							&Ni[i], &Nj[i], &ZaaR, &ZaaI, &ZbbR, &ZbbI, &ZccR, &ZccI, &ZnnR, &ZnnI, &ZabR, &ZabI, &ZacR, &ZacI, &ZanR, &ZanI, &ZbcR, &ZbcI, 
							&ZbnR, &ZbnI, &ZcnR, &ZcnI, &Tipo_cabo_aux, &Comprimento[i] );

					Zaa [i].real( ZaaR / Z_base );    Zaa[i].imag( ZaaI / Z_base );
					Zbb [i].real( ZbbR / Z_base );    Zbb[i].imag( ZbbI / Z_base );
					Zcc [i].real( ZccR / Z_base );    Zcc[i].imag( ZccI / Z_base );
					Zab [i].real( ZabR / Z_base );    Zab[i].imag( ZabI / Z_base );
					Zac [i].real( ZacR / Z_base );    Zac[i].imag( ZacI / Z_base );
					Zbc [i].real( ZbcR / Z_base );    Zbc[i].imag( ZbcI / Z_base );
					Zan [i].real( ZanR / Z_base );    Zan[i].imag( ZanI / Z_base );
					Zbn [i].real( ZbnR / Z_base );    Zbn[i].imag( ZbnI / Z_base );
					Zcn [i].real( ZcnR / Z_base );    Zcn[i].imag( ZcnI / Z_base );
					Znn [i].real( ZnnR / Z_base );    Znn[i].imag( ZnnI / Z_base );

					Tipo_Circuito.push_back ( Tipo_circuito_aux );
					Tipo_Cabo.push_back     ( Tipo_cabo_aux     );
			   }

			   else
			   {
					fscanf (inicio,"%d %d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %s %lf", 
							&Ni[i], &Nj[i], &ZaaR, &ZaaI, &ZbbR, &ZbbI, &ZccR, &ZccI, &ZnnR, &ZnnI, &ZabR, &ZabI, &ZacR, &ZacI, &ZanR, &ZanI, &ZbcR, &ZbcI, 
							&ZbnR, &ZbnI, &ZcnR, &ZcnI, &Tipo_cabo_aux, &Comprimento[i] );

				    Zaa [i] = complex<double> ( ZaaR , ZaaI ) * Comprimento[i] * Unidade_real_imp / Z_base;
					Zbb [i] = complex<double> ( ZbbR , ZbbI ) * Comprimento[i] * Unidade_real_imp / Z_base;
					Zcc [i] = complex<double> ( ZccR , ZccI ) * Comprimento[i] * Unidade_real_imp / Z_base;
					Zab [i] = complex<double> ( ZabR , ZabI ) * Comprimento[i] * Unidade_real_imp / Z_base;
					Zac [i] = complex<double> ( ZacR , ZacI ) * Comprimento[i] * Unidade_real_imp / Z_base;
					Zbc [i] = complex<double> ( ZbcR , ZbcI ) * Comprimento[i] * Unidade_real_imp / Z_base;
					Zan [i] = complex<double> ( ZanR , ZanI ) * Comprimento[i] * Unidade_real_imp / Z_base;
					Zbn [i] = complex<double> ( ZbnR , ZbnI ) * Comprimento[i] * Unidade_real_imp / Z_base;
					Zcn [i] = complex<double> ( ZcnR , ZcnI ) * Comprimento[i] * Unidade_real_imp / Z_base;
					Znn [i] = complex<double> ( ZnnR , ZnnI ) * Comprimento[i] * Unidade_real_imp / Z_base;

					Tipo_Circuito.push_back ( Tipo_circuito_aux );
					Tipo_Cabo.push_back     ( ""                );
			   }	
		   }

		   else 
		   {
			   fscanf (inicio,"%d %d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %s %lf", 
							&Ni[i], &Nj[i], &ZaaR, &ZaaI, &ZbbR, &ZbbI, &ZccR, &ZccI, &ZnnR, &ZnnI, &ZabR, &ZabI, &ZacR, &ZacI, &ZanR, &ZanI, &ZbcR, &ZbcI, 
							&ZbnR, &ZbnI, &ZcnR, &ZcnI, &Comprimento[i] );

				Zaa [i] = 0;
				Zbb [i] = 0;
				Zcc [i] = 0;
				Zab [i] = 0;
				Zac [i] = 0;
				Zbc [i] = 0;
				Zan [i] = 0;
				Zbn [i] = 0;
				Zcn [i] = 0;
				Znn [i] = 0;

				Tipo_Circuito.push_back ( Tipo_circuito_aux );
		   }
		}

//------------------------------------------------------------------------------------------------------------------
// Calcula as impedâncias de sequência
//------------------------------------------------------------------------------------------------------------------

	for ( i = 0; i < Numero_linhas; ++i) 
	{
		Z0 [i] = (1.0/3.0)*(Zaa [i] + Zbb [i] + Zcc [i]) + 2.0/3.0* (Zab [i] + Zbc [i] + Zac [i]);
		Z1 [i] = (1.0/3.0)*(Zaa [i] + Zbb [i] + Zcc [i]) - 1.0/3.0* (Zab [i] + Zbc [i] + Zac [i]);
	}

//------------------------------------------------------------------------------------------------------------------
// Pega a barra da subestação (Tipo da barra = 3)
//------------------------------------------------------------------------------------------------------------------
	
	for ( i = 0; i < Numero_barras; i++)
	{
		if ( Tipo_barras [i] == 3)
		{
			BarraSub = Barras [i];
			break;
		}
	}

//------------------------------------------------------------------------------------------------------------------
// Rotina de Ordenação e Renumeração
//------------------------------------------------------------------------------------------------------------------

	ordenamento_barras (Ni, Nj, Ramo, Numero_linhas);

	//------------------------------------------------------------------------------------------------------------------
	// Leitura dos parâmetros de entrada.
	//------------------------------------------------------------------------------------------------------------------

	FILE *inicio_2;
	if(!(inicio_2 = fopen ( "Parametros.txt" ,"r"))){ printf("Erro ao tentar abrir o arquivo: sistema"); getch();}

	fscanf( inicio_2, "%s%s%f %s%s%d %s%s%f %s%s%f", &Texto_lixo, &Texto_lixo, &K_religador, &Texto_lixo, &Texto_lixo, &aux_intervalo, &Texto_lixo, &Texto_lixo, &Intervalo_Coord_rele_fusivel, &Texto_lixo, &Texto_lixo, &Intervalo_Coord_rele_rele );
	fscanf( inicio_2, "%s%s%f %s%s%f %s%s%f       ", &Texto_lixo, &Texto_lixo, &Intervalo_Coord_rele_religador, &Texto_lixo, &Texto_lixo, &Intervalo_Coord_religador_religador, &Texto_lixo, &Texto_lixo, &Intervalo_Coord_religador_fusivel );
	fscanf( inicio_2, "%s%s%f %s%s%f %s%s%f       ", &Texto_lixo, &Texto_lixo, &Dial_min, &Texto_lixo, &Texto_lixo, &Dial_max, &Texto_lixo, &Texto_lixo, &FI );
	fscanf( inicio_2, "%s%s%f %s%s%f %s%s%f       ", &Texto_lixo, &Texto_lixo, &Delta_tap, &Texto_lixo, &Texto_lixo, &FS, &Texto_lixo, &Texto_lixo, &FT );
	fscanf( inicio_2, "%s%s%d %s%s%s %s%s%f       ", &Texto_lixo, &Texto_lixo, &Tipo_coordenacao, &Texto_lixo, &Texto_lixo, &Elo_Preferencial, &Texto_lixo, &Texto_lixo, &ZC );
	fscanf( inicio_2, "%s%s%f %s%s%f %s%s%lf      ", &Texto_lixo, &Texto_lixo, &taxa, &Texto_lixo, &Texto_lixo, &anos, &Texto_lixo, &Texto_lixo, &Convergencia );
	fscanf( inicio_2, "%s%s%f %s%s%f %s%s%d %s%s%d", &Texto_lixo, &Texto_lixo, &K_desequilibrio, &Texto_lixo, &Texto_lixo, &const_k, &Texto_lixo, &Texto_lixo, &Coordenado_ou_seletivo, &Texto_lixo, &Texto_lixo, &Modo_calculo_I_carga);

	//------------------------------------------------------------------------------------------------------------------
	// Adiciona o tipo das curvas e a norma das curvas na struct
	//------------------------------------------------------------------------------------------------------------------

	for (i = 0; i < DISJUNTORPROT.size (); i++)
	{
		if (DISJUNTORPROT[i].Norma_Curva == 1)
		{
			DISJUNTORPROT[i].Norma_Curva_string = "IEC/ABNT";

			if (DISJUNTORPROT[i].Tipo_Curva == 1)
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Inversa";
			}
			else if (DISJUNTORPROT[i].Tipo_Curva == 2)
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Muito Inversa";
			}
			else if (DISJUNTORPROT[i].Tipo_Curva == 3)
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Extremamente Inversa";
			}
			else
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Pouco Inversa";
			}
		}
		else if (DISJUNTORPROT[i].Norma_Curva == 2)
		{
			DISJUNTORPROT[i].Norma_Curva_string = "IAC";

			if (DISJUNTORPROT[i].Tipo_Curva == 1)
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Inversa";
			}
			else if (DISJUNTORPROT[i].Tipo_Curva == 2)
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Muito Inversa";
			}
			else if (DISJUNTORPROT[i].Tipo_Curva == 3)
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Extremamente Inversa";
			}
			else
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Pouco Inversa";
			}
		}
		else if (DISJUNTORPROT[i].Norma_Curva == 3)
		{
			DISJUNTORPROT[i].Norma_Curva_string = "US";

			if (DISJUNTORPROT[i].Tipo_Curva == 1)
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Inversa";
			}
			else if (DISJUNTORPROT[i].Tipo_Curva == 2)
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Muito Inversa";
			}
			else if (DISJUNTORPROT[i].Tipo_Curva == 3)
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Extremamente Inversa";
			}
			else if (DISJUNTORPROT[i].Tipo_Curva == 4)
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Pouco Inversa";
			}
			else
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Moderadamente Inversa";
			}
		}
		else
		{
			DISJUNTORPROT[i].Norma_Curva_string = "ANSI/IEEE";

			if (DISJUNTORPROT[i].Tipo_Curva == 1)
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Muito Inversa";
			}
			else if (DISJUNTORPROT[i].Tipo_Curva == 2)
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Extremamente Inversa";
			}
			else
			{
				DISJUNTORPROT[i].Tipo_Curva_string = "Moderamente Inversa";
			}
		}
	}

	for (i = 0; i < CHAVEPROT.size (); i++)
	{
		if (CHAVEPROT[i].Religador_Norma_Curva == 1)
		{
			CHAVEPROT[i].Norma_Curva_string = "IEC/ABNT";

			if (CHAVEPROT[i].Religador_Tipo_Curva == 1)
			{
				CHAVEPROT[i].Tipo_Curva_string = "Inversa";
			}
			else if (CHAVEPROT[i].Religador_Tipo_Curva == 2)
			{
				CHAVEPROT[i].Tipo_Curva_string = "Muito Inversa";
			}
			else if (CHAVEPROT[i].Religador_Tipo_Curva == 3)
			{
				CHAVEPROT[i].Tipo_Curva_string = "Extremamente Inversa";
			}
			else
			{
				CHAVEPROT[i].Tipo_Curva_string = "Pouco Inversa";
			}
		}
		else if (CHAVEPROT[i].Religador_Norma_Curva == 2)
		{
			CHAVEPROT[i].Norma_Curva_string = "IAC";

			if (CHAVEPROT[i].Religador_Tipo_Curva == 1)
			{
				CHAVEPROT[i].Tipo_Curva_string = "Inversa";
			}
			else if (CHAVEPROT[i].Religador_Tipo_Curva == 2)
			{
				CHAVEPROT[i].Tipo_Curva_string = "Muito Inversa";
			}
			else if (CHAVEPROT[i].Religador_Tipo_Curva == 3)
			{
				CHAVEPROT[i].Tipo_Curva_string = "Extremamente Inversa";
			}
			else
			{
				CHAVEPROT[i].Tipo_Curva_string = "Pouco Inversa";
			}
		}
		else if (CHAVEPROT[i].Religador_Norma_Curva == 3)
		{
			CHAVEPROT[i].Norma_Curva_string = "US";

			if (CHAVEPROT[i].Religador_Tipo_Curva == 1)
			{
				CHAVEPROT[i].Tipo_Curva_string = "Inversa";
			}
			else if (CHAVEPROT[i].Religador_Tipo_Curva == 2)
			{
				CHAVEPROT[i].Tipo_Curva_string = "Muito Inversa";
			}
			else if (CHAVEPROT[i].Religador_Tipo_Curva == 3)
			{
				CHAVEPROT[i].Tipo_Curva_string = "Extremamente Inversa";
			}
			else  if (CHAVEPROT[i].Religador_Tipo_Curva == 4)
			{
				CHAVEPROT[i].Tipo_Curva_string = "Pouco Inversa";
			}
			else 
			{
				CHAVEPROT[i].Tipo_Curva_string = "Moderadamente Inversa";
			}
		}
		else if (CHAVEPROT[i].Religador_Norma_Curva == 4)
		{
			CHAVEPROT[i].Norma_Curva_string = "ANSI/IEEE";

			if (CHAVEPROT[i].Religador_Tipo_Curva == 1)
			{
				CHAVEPROT[i].Tipo_Curva_string = "Muito Inversa";
			}
			else if (CHAVEPROT[i].Religador_Tipo_Curva == 2)
			{
				CHAVEPROT[i].Tipo_Curva_string = "Extremamente Inversa";
			}
			else
			{
				CHAVEPROT[i].Tipo_Curva_string = "Moderamente Inversa";
			}
		}
	}
}

void Calculo_do_fluxo::ordenamento_barras (int * Ni, int * Nj, int * Ramo,  int Numero_linhas)
{
   barra_trocada      = 0;
   j                  = 0; // inicializando valores dos registradores
   k                  = 0; // inicializando valores dos registradores
   IndexRamo          = new int [ Numero_linhas ];
   IndexStruct        = new int [ Numero_linhas ];
   IndexStructTudo    = new int [ Numero_linhas ];
   BarrasProcessadas  = new int [ Numero_linhas ];
   Apontador          = new int [ Numero_linhas ];
   Nj_ord             = new int [ Numero_linhas ];
   Ni_ord             = new int [ Numero_linhas ];
   Index              = new int [ Numero_linhas ];
   IndexBarra         = new int [ Numero_linhas ];
   Linha_A            = new int [ Numero_linhas ];
   Linha_B            = new int [ Numero_linhas ];
   Linha_C            = new int [ Numero_linhas ];
   aux                = BarraSub; //inicializa com o valor da subestação
   memset (Index, 0, Numero_linhas*sizeof(int)); //Inicializa com 0
  

   for (i = 0; i < Numero_linhas ; ++i)
	   {
		   if (Ni [i] == BarraSub)
		   {
			   Ni_ord    [j] = Ni [i];
			   Nj_ord    [j] = Nj [i];
			   IndexRamo [j] = i;
			   Index     [i] = 1;
			   ++j;
		   }

		   else if ( Nj [i] == BarraSub)
		   {
			   Ni_ord    [j] = Nj [i];
			   Nj_ord    [j] = Ni [i];
			   IndexRamo [j] = i;
			   Index     [i] = 1;
		       ++j;
		   }
       }

   while (j < Numero_linhas )
   {
	   for (i = 0; i < Numero_linhas ; ++i)
	   {
		   if (k == 772)
		   {
			   int oioioioioi = 1;
		   }
		   if (Nj_ord [k] == Ni [i] && Index [i] == 0)
		   {
			   Ni_ord    [j] = Nj_ord [k];
			   Nj_ord    [j] = Nj     [i];
			   IndexRamo [j] = i;
			   Index     [i] = 1;
			   j++;
		   }

		   else if (Nj_ord [k] == Nj [i] && Index [i] == 0)
		   {
			   Ni_ord    [j] = Nj     [i];
			   Nj_ord    [j] = Nj_ord [k];
			   IndexRamo [j] = i;
			   Index     [i] = 1;
			   j++;
		   }
	   }
    k++;

   }
   
   //------------------------------------------------------------------------------------------------------------------
   // Calculo do IndexBarra
   //------------------------------------------------------------------------------------------------------------------

	for ( i = 0; i < Numero_barras; i++)
	{
		if( Barras [i] == BarraSub )
		{
			IndexBarra [0] = i;
			break;
		}
	}

   c1 = 1;

   for ( j = 0; j < Numero_linhas; j++)
   {
		for ( i = 0; i < Numero_barras; i++)
		{
			if ( Nj_ord [j] == Barras [i])
			{
				IndexBarra [c1] = i;
				c1 ++;
				break;
			}			
		}
   }
   
   
 //  for (i = 0; i < Numero_barras ; ++i)
 //  {
	//printf ("Nj_ord = %d \t Inedex_Barra = %d \n", Nj_ord [i], IndexBarra [i+1]);
 //  }
   

   //------------------------------------------------------------------------------------------------------------------
   // Rotina de Renumeração
   //------------------------------------------------------------------------------------------------------------------

	renumaracao_barras (Ni, Nj, Ramo, Numero_linhas, IndexRamo, Ni_ord, Nj_ord);
}

void Calculo_do_fluxo::renumaracao_barras (int * Ni, int * Nj, int * Ramo, int Numero_linhas, int * IndexRamo, int * Ni_ord, int * Nj_ord)
{
		i, j         = 0;
		Nj_renum     = new int [ Numero_linhas ];
		Ni_renum     = new int [ Numero_linhas ];
		Barras_renum = new int [ Numero_barras ];
		Ni_renum [0] = 0; //inicializa as variáveis
		Nj_renum [0] = 1;

		for (i = 1; i < Numero_linhas ; ++i) //monta Ni_ord_num e atribui Nj_renum = Nj_ord
		{
			if (Nj_ord [i] == Nj_ord [i-1])
			{
				Nj_renum [i] = Ni_renum [i-1];
			}
			else
			{
				Nj_renum [i] = Nj_renum [i-1] + 1;
			}
		}

	
		for (j = 1; j < Numero_linhas ; ++j)// monta Nj_renum
		{
			if (Ni_ord [j] == Ni_ord [j-1])
				{
					Ni_renum [j] = Ni_renum [j-1];
				}
			else 
			{
				for (i = 0; i < Numero_linhas ; ++i)
					{
						if (Ni_ord [j] == Nj_ord [i])
						{
							Ni_renum [j] = Nj_renum [i];
							break;
						}
					}
			}
		}

	   /*	
	   for (i = 0; i < Numero_linhas ; ++i)
	   {
	   printf ("Ni_ord = %d \t Nj_ord = %d \t Ni_renum = %d \t Nj_renum = %d\n", Ni_ord [i],  Nj_ord [i], Ni_renum [i],  Nj_renum [i]);
	   }
	   */
	
	//------------------------------------------------------------------------------------------------------------------
	// Traduz renumera as barras nas quais as cargas estão conectadas
	//------------------------------------------------------------------------------------------------------------------

	for (i = 0; i < Numero_barras; ++i)
	{
		for (j = 0; j < Numero_linhas; ++j)
		{
			if (Barras [i] == Ni_ord [j])
			{
				Barras_renum [i] = Ni_renum [j];
			}
			else if (Barras [i] == Nj_ord [j])
			{
				Barras_renum [i] = Nj_renum [j];
			}
		}
		// printf ("%d %d\n", Barras [i], Barras_renum [i]);
	}
		// fluxo_potencia_mono (Ni_renum, Nj_renum, Barras_renum, IndexRamo, Ni_ord, Nj_ord, Barras, Sa, Sb, Sc, Ca, Cb, Cc, Zaa, Zab, Zac, Zbb, Zbc, Zcc, Zan, Zbn, Zcn, Znn, Numero_barras);
}

void Calculo_do_fluxo::fluxo_potencia_mono ()
{
	Convergiu    = 0;
	    
	//------------------------------------------------------------------------------------------------------------------
	// Inicializando os valores da tensão de referência
	//------------------------------------------------------------------------------------------------------------------

	for (i = 0; i < Numero_barras; ++i)
	{
		Va_barra [i] = V_base/V_ref;
	}

	while (Convergiu < 1)
	{	
		Delta_Sa [0] = Va_barra [0] * conj (Ia_linha [0]);

		for ( i = 0; i < Numero_barras; ++i)
		{
			Ia_nodal [i] = conj( (- Sa [IndexBarra [i]] + Ca [IndexBarra [i]] ) / Va_barra [i] ); 
			//printf (" Ia_nodal  = %8.3f%8.3f\n", real(Ia_nodal[i]),imag(Ia_nodal[i]) );
		}

		memset (Ia_linha, 0, Numero_barras*sizeof(complex<double>));

		for (i = Numero_barras - 1; i > 0; --i)
		{	
			Ia_linha [i]              -= Ia_nodal [i];
			Ia_linha [Ni_renum [i-1]] += Ia_linha [i];
		}

		for (i = 0; i < Numero_barras; i++)
		{
			//printf ("Barra = %d \t I_linha = %.4g + i%.4g \t I linha = %.4g + i%.4g \n", i, Ia_linha [i], Ia_linha [i]);
		}
		
		//------------------------------------------------------------------------------------------------------------------
		// Calcula A tensão nas barras
		//------------------------------------------------------------------------------------------------------------------

		for (i = 0; i < Numero_linhas; ++i )
		{
			Va_barra [ Nj_renum [i] ] = Va_barra [ Ni_renum [i] ] - Zaa [ IndexRamo [i] ] * Ia_linha [i+1];
			//printf (" i %d V_barra  = %20.9f + i%20.9f \n", i+1, real(Va_barra [i+1]), imag(Va_barra[i+1]));
		}

		for (i = 0; i < Numero_barras; i++)
		{
			//printf ("Barra = %d\tI_linha = %-10.2f + i%-10.2f\tTensao = %-6.2f + i%-6.2f \n", i, real (Ia_linha [i]), imag (Ia_linha [i]), real (Va_barra [i]), imag (Va_barra [i]) );
		}

		//------------------------------------------------------------------------------------------------------------------
		// Calcula as diferenças de potência
		//------------------------------------------------------------------------------------------------------------------

		Delta_Sa [1] = Va_barra [0] * conj (Ia_linha [0]);
		if ( abs (Delta_Sa [0] - Delta_Sa [1]) < Convergencia)
		{
			Convergiu = 2;
		}
	  }

		for (i = 0; i < Numero_barras; i++)
		{
			//printf (" Barra = %-3dbTensao = %-6.5f + i%-6.4f \n", i, real (Va_barra [i]), imag (Va_barra [i]) );
		}	

		Perdas = 0.0; // condição inicial

		for (i = 0; i < Numero_linhas; i++)
		{
			Perdas += abs (pow ((Ia_linha [i+1]), 2.0)*(real (Zaa [IndexRamo [i]])));	
		}
}

void Calculo_do_fluxo::fluxo_potencia_tri ()
{
	Convergiu    = 0;
	complex <double> Angle_120 ( -0.5,  0.866025403784 );
	complex <double> Angle_240 ( -0.5, -0.866025403784 );
    
	//------------------------------------------------------------------------------------------------------------------
	// Inicializando os valores da tensão de referência
	//------------------------------------------------------------------------------------------------------------------

	for (i = 0; i < Numero_barras; ++i)
	{
		Va_barra [i] = V_base/V_ref;
		Vb_barra [i] = V_base/V_ref * (Angle_240); // colocar as fases (-120)
		Vc_barra [i] = V_base/V_ref * (Angle_120); //Angle_240colocar as fases (120)
	}

	while (Convergiu < 1)
	{	
		
		Delta_Sa [0] = Va_barra [0] * conj (Ia_linha [0]);
		Delta_Sb [0] = Vb_barra [0] * conj (Ib_linha [0]);
		Delta_Sc [0] = Vc_barra [0] * conj (Ic_linha [0]);

		for ( i = 0; i < Numero_barras; ++i)
		{
			Ia_nodal [i] = conj ((-Sa[IndexBarra [i]] + Ca[IndexBarra [i]]) / Va_barra [i]);
			Ib_nodal [i] = conj ((-Sb[IndexBarra [i]] + Cb[IndexBarra [i]]) / Vb_barra [i]);
			Ic_nodal [i] = conj ((-Sc[IndexBarra [i]] + Cc[IndexBarra [i]]) / Vc_barra [i]);
		}

		memset (Ia_linha, 0, Numero_barras*sizeof(complex<double>)); // zera as correntes nas linhas da iteração passada
		memset (Ib_linha, 0, Numero_barras*sizeof(complex<double>));
		memset (Ic_linha, 0, Numero_barras*sizeof(complex<double>));

		for (i = Numero_barras - 1; i > 0; --i)
		{	
			Ia_linha [i]              -= Ia_nodal [i];
			Ib_linha [i]              -= Ib_nodal [i];
			Ic_linha [i]              -= Ic_nodal [i];
			Ia_linha [Ni_renum [i-1]] += Ia_linha [i];
			Ib_linha [Ni_renum [i-1]] += Ib_linha [i];
			Ic_linha [Ni_renum [i-1]] += Ic_linha [i];
			//printf (" Ia_linha  = %8.3f Ib_linha  = %8.3f Ic_linha  = %8.3f\n", abs (Ia_linha[i])* I_base, abs (Ib_linha[i])* I_base, abs (Ic_linha[i])* I_base);
		}
		
		//------------------------------------------------------------------------------------------------------------------
		// Calcula A tensão nas barras
		//------------------------------------------------------------------------------------------------------------------

		for (i = 0; i < Numero_linhas; ++i )
		{
			Va_barra [ Nj_renum [i] ] = Va_barra [ Ni_renum [i] ] - Zaa [ IndexRamo [i] ] * Ia_linha [i+1];
			Vb_barra [ Nj_renum [i] ] = Vb_barra [ Ni_renum [i] ] - Zbb [ IndexRamo [i] ] * Ib_linha [i+1];
			Vc_barra [ Nj_renum [i] ] = Vc_barra [ Ni_renum [i] ] - Zcc [ IndexRamo [i] ] * Ic_linha [i+1];
		}

		//------------------------------------------------------------------------------------------------------------------
		// Calcula as diferenças de potência
		//------------------------------------------------------------------------------------------------------------------

		Delta_Sa [1] = Va_barra [0] * conj (Ia_linha [0]);
		Delta_Sb [1] = Vb_barra [0] * conj (Ib_linha [0]);
		Delta_Sc [1] = Vc_barra [0] * conj (Ic_linha [0]);
		
		if ( (abs(Delta_Sa[0] - Delta_Sa[1])) && (abs(Delta_Sb[0] - Delta_Sb[1])) && (abs(Delta_Sc[0] - Delta_Sc[1])) < Convergencia )
		{
			Convergiu = 2;
		}
	  }

		Perdas = 0.0; // condição inicial
		
		for (i = 0; i < Numero_linhas; i++)
		{
			Perdas += abs (pow ((Ia_linha [i+1]), 2.0)*(real (Zaa [IndexRamo [i]]))) + abs(pow((Ib_linha [i+1]), 2.0)*(real (Zbb[IndexRamo [i]]))) + abs(pow((Ic_linha [i+1]), 2.0)*(real(Zcc[IndexRamo[i]])));	
		}
		
		float Perdas_Real;
		Perdas_Real = Perdas * S_base;
		//------------------------------------------------------------------------------------------------------------------
		// Cálculo das correntes de carga
		//------------------------------------------------------------------------------------------------------------------

		double Fator_K = pow (1.0 + taxa, anos); //fator de crescimento de carga
	
		for (i = 0 ; i < Numero_barras ; i++)     
		{
			Ia_carga [i] = abs(Ia_linha [i]) * Fator_K * I_base;
			Ib_carga [i] = abs(Ib_linha [i]) * Fator_K * I_base;
			Ic_carga [i] = abs(Ic_linha [i]) * Fator_K * I_base;

			if (Ia_carga [i] > Ib_carga [i])
			{
				if (Ia_carga [i] > Ic_carga [i])
				{
					I_carga_max [i] = Ia_carga [i];
				}
				else
				{
					I_carga_max [i] = Ic_carga [i];
				}
			}
			else if (Ib_carga [i] > Ic_carga [i])
			{
				I_carga_max [i] = Ib_carga [i]; 
			}
			else
			{
				I_carga_max [i] = Ic_carga [i];
			}
		}

		//------------------------------------------------------------------------------------------------------------------
		// Adiciona os valores de Ni, Nj, Icarga e Ramos na estrutura
		//------------------------------------------------------------------------------------------------------------------
	
	
		for (i = 0 ; i < TRAFOS_DISTRI.size() ; i++)     
		{
			for (j = 0 ; j < Numero_barras ; j++)
			{
				if (TRAFOS_DISTRI [i].Ramo_ini == IndexRamo [j])
				{
					TRAFOS_DISTRI [i].Ni_renum = Ni_renum [j];
					TRAFOS_DISTRI [i].Nj_renum = Nj_renum [j];
					TRAFOS_DISTRI [i].Ramo_ord = j;
					break;
				}
			}
		}
	
		for (i = 0 ; i < DISJUNTORPROT.size() ; i++)     
		{
			for (j = 0 ; j < Numero_barras ; j++)
			{
				if (DISJUNTORPROT [i].Ramo_ini == IndexRamo [j])
				{
					DISJUNTORPROT [i].Ni_renum = Ni_renum    [j];
					DISJUNTORPROT [i].Nj_renum = Nj_renum    [j];
					DISJUNTORPROT [i].Ramo_ord = j;
					break;
				}
			}
		}
	
		for (i = 0 ; i < CHAVEPROT.size() ; i++)     
		{
			for (j = 0 ; j < Numero_barras ; j++)
			{
				if (CHAVEPROT [i].Ramo_ini == IndexRamo [j])
				{
					CHAVEPROT [i].Ni_renum = Ni_renum    [j];
					CHAVEPROT [i].Nj_renum = Nj_renum    [j];
					CHAVEPROT [i].Ramo_ord = j;
					break;
				}
			}
		}

       //------------------------------------------------------------------------------------------------------------------
       // Rotina de escrita dos dados no txt
       //------------------------------------------------------------------------------------------------------------------
      
       FILE    * pFile;
       pFile   = fopen ("Resultado_Fluxo_Tri.txt","w"); 
       fprintf (pFile, "                                      Resultado do Fluxo de Potência                                      \n");
       fprintf (pFile, " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  \n");
	   fprintf (pFile, "|        |                |              |                |              |                |              |\n");
	   fprintf (pFile, "| Barra  |     |Va|       |  < Va        |     |Vb|       |  < Vb        |     |Vc|       |  < Vc        |\n");
       fprintf (pFile, "|_ _ _ _ | _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ | _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ | _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ |\n");

	   for (i = 1 ; i < Numero_barras ; i++)     
       {
	     fprintf (pFile, "|%8d|%16.5f|%14.5f|%16.5f|%14.5f|%16.5f|%14.5f|\n", 
		          Nj_ord [i-1], abs (Va_barra [i]) * V_base, arg (Va_barra [i])*180.0/3.141592, abs (Vb_barra [i]) * V_base, arg (Vb_barra [i])*180.0/3.141592,
				  abs (Vc_barra [i]) * V_base, arg (Vc_barra [i])*180.0/3.141592);
       }

       fprintf (pFile, "|_ _ _ _ | _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ | _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ | _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ |\n");
	   fprintf (pFile, "\n\n\n");
	   fprintf (pFile, " _ _ _ _ _  _ _ _ _ _ _  _ _ _ _ _ _  _ _ _ _ _ _  _ _ _ _ _ _  _ _ _ _ _ _  _ _ _ _ _ _ _ \n");
	   fprintf (pFile, "|           |            |            |            |            |            |            |\n");
	   fprintf (pFile, "|   Barras  |    |Ia|    |    < Ia    |    |Ib|    |    < Ib    |    |Ic|    |   < Ic     |\n");
       fprintf (pFile, "|_  _ _ _ _ | _ _ _ _ _ _| _ _ _ _ _ _| _ _ _ _ _ _| _ _ _ _ _ _| _ _ _ _ _ _| _ _ _ _ _ _|\n");
	 
	   for (i = 1 ; i < Numero_barras ; i++)     
       {
	     fprintf (pFile, "|%-5d-%5d|%12.5f|%12.5f|%12.5f|%12.5f|%12.5f|%12.5f|\n", 
		          Nj_ord [i-1], Ni_ord [i-1], abs (Ia_linha [i]*S_base/V_base), arg (Ia_linha [i]*S_base/V_base) * 180.0/3.141592 , abs (Ib_linha [i]*S_base/V_base), arg (Ib_linha [i]*S_base/V_base) * 180.0/3.141592,
				  abs (Ic_linha [i]*S_base/V_base), arg (Ic_linha [i]*S_base/V_base) * 180.0/3.141592 );
       }

       fprintf (pFile, "|_  _ _ _ _ | _ _ _ _ _ _| _ _ _ _ _ _| _ _ _ _ _ _| _ _ _ _ _ _| _ _ _ _ _ _| _ _ _ _ _ _|\n");
	   fclose (pFile);
}

void Calculo_do_fluxo::curto_circuito ()
{
	Z0_eq = new complex <double> [ Numero_barras ];
	Z1_eq = new complex <double> [ Numero_barras ];

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Mudança de base (PU) das impedâncias da subestação
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	complex <double>   Z0_sub ( R0_sub/100, X0_sub/100 );
	complex <double>   Z1_sub ( R1_sub/100, X1_sub/100 );
	
	Z0_sub *= pow (V_baixa_sub*1000, 2) / (S_sub*1e3) * S_base / (pow (V_base, 2));
	Z1_sub *= pow (V_baixa_sub*1000, 2) / (S_sub*1e3) * S_base / (pow (V_base, 2));

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Inicia o Relógio
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
	/*LONGLONG start, end;
	double cycles, average_cycles=0;
	double pico, nano, micro, milli, seconds;

	average_cycles = get_average_cycles();

	pico = (1.000000e+12) / average_cycles;
	nano = (1.000000e+09) / average_cycles;
	micro = (1.000000e+06) / average_cycles;
	milli = 1000.0 / average_cycles;
	seconds = 1.0 / average_cycles;

	int k1;
	double time_in_seconds [ 10000 ];
	double tempo_medio = 0;
	for ( k1 = 0; k1 < 10000; k1++)
	{
	clock_t start_time;
	start_time = clock();
	}
	*/

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// A impedância dos ramos que estão conectados à subestação tem a impedância dela somada
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Z0_eq [0] = Z0_sub;
	Z1_eq [0] = Z1_sub;

	for ( i = 0; i < Numero_linhas; i++)
	{
		Z1_eq [i+1] = Z1 [IndexRamo [i]] + Z1_eq [Ni_renum [i]]; 
		Z0_eq [i+1] = Z0 [IndexRamo [i]] + Z0_eq [Ni_renum [i]];
	}

	/* Metodologia do TCC

	for (i = 0; i < Numero_linhas; i++)
	{
		aux = Ni_renum [i];
		Z0_eq [i+1] = Z0 [IndexRamo [i]];
		Z1_eq [i+1] = Z1 [IndexRamo [i]];

		while ( aux != 0 ) // enquanto não tiver chegado na barra da subestação
		{
			for (j = 0; j < i+1; j++)
			{
				if (Nj_renum [j] == Ni_renum [i])
				{
					Z0_eq [i+1] += Z0_eq [j+1];
					Z1_eq [i+1] += Z1_eq [j+1];
					aux = 0;
					break;
				}
			}

			if ( aux == 0 )
			{
				break;
			}

			for ( j = 0; j < Numero_barras; j++)
			{
				if (aux == Ni_renum [j])
				{
					Z0_eq [i+1] += Z0 [IndexRamo [j]];
					Z1_eq [i+1] += Z1 [IndexRamo [j]];
					aux = Ni_renum [j];
				}
			}
		}
	}

	for (i = 0; i < Numero_barras; i++) // Adiciona as impedâncias da subestação
	{
		//Z0_eq     [i+1] += Z0_sub;
		//Z1_eq     [i+1] += Z1_sub;
	}

	*/

	//------------------------------------------------------------------------------------------------------------------
    // Cálculo das correntes de curto-circuito
    //------------------------------------------------------------------------------------------------------------------

    float F_As [51] = {1, 1, 1.02, 1.04, 1.07, 1.10, 1.13, 1.16, 1.19, 1.21, 1.24, 1.26, 1.28, 1.30, 1.32, 1.34, 1.35, 1.37, 1.38, 1.39, 1.40, 1.41, 1.42, 1.43, 1.46, 1.47, 1.49, 1.51, 1.52, 1.53, 1.54, 1.55, 1.56, 1.57, 1.58, 1.59, 1.60, 1.61, 1.62, 1.64, 1.67, 1.68, 1.69, 1.70, 1.71, 1.71, 1.71, 1.72, 1.72, 1.73, 1.73 };
    float X_R  [51] = {0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3, 3.2, 3.4, 3.6, 3.8, 4, 4.2, 4.4, 4.6, 4.8, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10, 11, 12, 13, 14, 15, 20, 30, 40, 50, 60, 70, 80, 100, 200, 400, 600, 1000 };
	float aux, K,K_zero;	 
	ZC = ZC / Z_base;

	for (i = 0; i < Numero_barras; i++)
	{
		X_Barra_R      [i] = imag (Z1_eq [i]) / real (Z1_eq [i]);
		X_Barra_R_zero [i] = ( 2.0 * imag (Z1_eq [i]) + imag (Z0_eq [i])) / (2.0 * real (Z1_eq [i]) + real (Z0_eq [i]));
		Icc_3ph        [i] = abs  (1.0 / Z1_eq [i]);
		Icc_2ph        [i] = 0.865 * Icc_3ph [i];
		Icc_1ph        [i] = abs  (3.0 / ( 2.0 * Z1_eq [i] + Z0_eq [i]));
		Icc_1ph_min    [i] = abs  (3.0 / ( 3.0 * ZC + 2.0 * Z1_eq [i] + Z0_eq [i] )); // Considernado uma impedância de contato de 40/3 ohms

		for (j = 0; j < 51; j++) // Interpolação dos dados
		{
			if (X_Barra_R [i] < X_R [0])
			{
				K = F_As [0];
			}
			else if ( X_Barra_R [i] > X_R [50])
			{
				K = F_As [50];
			}
			else if (X_Barra_R [i] < X_R [j])
			{
				aux = (F_As [j] - F_As [j-1]) / (X_R [j] - X_R [j-1]);
				K   =  aux * ( X_Barra_R [i] - X_R [j-1]) + F_As [j-1];
				break;
			}
		}

		for (j = 0; j < 51; j++) // Interpolação dos dados
		{
			if (X_Barra_R_zero [i] < X_R [0])
			{
				K_zero = F_As [0];
			}
			else if ( X_Barra_R_zero [i] > X_R [50])
			{
				K_zero = F_As [50];
			}
			else if (X_Barra_R_zero [i] < X_R [j])
			{
				aux = (F_As [j] - F_As [j-1]) / (X_R [j] - X_R [j-1]);
				K_zero   =  aux * ( X_Barra_R_zero [i] - X_R [j-1]) + F_As [j-1];
				break;
			}
		}

		Icc_3ph_As [i] = Icc_3ph [i] * K;
		Icc_2ph_As [i] = Icc_2ph [i] * K;
		Icc_1ph_As [i] = Icc_1ph [i] * K_zero;

		if (Icc_1ph_As [i] > Icc_3ph_As [i]) // Cálculo das correntes de curto-circuito máximas
		{

			Icc_max [i] = Icc_1ph_As [i];
		}
		else
		{
			Icc_max [i] = Icc_3ph_As [i];
		}
	}
	
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Adiciona as correntes de curto-circuito máximas, mínimas (monofásica e bifásica) na estrutura das chaves (CHAVEPROT)
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------

	for (i = 0; i < CHAVEPROT.size (); i++)
	{
		CHAVEPROT [i].Icc_max   = Icc_max     [CHAVEPROT [i].Nj_renum] * I_base;
		CHAVEPROT [i].Icc1f     = Icc_1ph_As  [CHAVEPROT [i].Nj_renum] * I_base;
		CHAVEPROT [i].Icc1f_min = Icc_1ph_min [CHAVEPROT [i].Nj_renum] * I_base;
		CHAVEPROT [i].Icc2f_min = Icc_2ph     [CHAVEPROT [i].Nj_renum] * I_base;
		CHAVEPROT [i].Icc3f     = Icc_3ph_As  [CHAVEPROT [i].Nj_renum] * I_base;
	}

	for (i = 0; i < DISJUNTORPROT.size (); i++)
	{
		DISJUNTORPROT [i].Icc_max   = Icc_max     [DISJUNTORPROT [i].Nj_renum] * I_base;
		DISJUNTORPROT [i].Icc1f     = Icc_1ph_As  [DISJUNTORPROT [i].Nj_renum] * I_base;
		DISJUNTORPROT [i].Icc1f_min = Icc_1ph_min [DISJUNTORPROT [i].Nj_renum] * I_base;
		DISJUNTORPROT [i].Icc2f_min = Icc_2ph     [DISJUNTORPROT [i].Nj_renum] * I_base;
		DISJUNTORPROT [i].Icc3f     = Icc_3ph_As  [DISJUNTORPROT [i].Nj_renum] * I_base;
	}

	for (i = 0; i < TRAFOS_DISTRI.size (); i++)
	{
		TRAFOS_DISTRI [i].Icc_max   = Icc_max     [TRAFOS_DISTRI [i].Nj_renum] * I_base;
		TRAFOS_DISTRI [i].Icc1f     = Icc_1ph_As  [TRAFOS_DISTRI [i].Nj_renum] * I_base;
		TRAFOS_DISTRI [i].Icc1f_min = Icc_1ph_min [TRAFOS_DISTRI [i].Nj_renum] * I_base;
		TRAFOS_DISTRI [i].Icc2f_min = Icc_2ph     [TRAFOS_DISTRI [i].Nj_renum] * I_base;		
		TRAFOS_DISTRI [i].Icc3f     = Icc_3ph_As  [TRAFOS_DISTRI [i].Nj_renum] * I_base;
	}


	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Finaliza o Relógio
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	/*start = read_tsc();
	printf("\n\nOperation took %.0f CPU cycles\n" "%f nanoseconds\n" "%f microseconds\n" "%f milliseconds\n" "%f seconds\n", (double)read_tsc()-start, 
		  ((double)read_tsc()-start)*nano, ((double)read_tsc()-start)*micro,((double)read_tsc()-start)*milli, ((double)read_tsc()-start)*seconds);*/

	/*
	time_in_seconds [k1] = (clock() - start_time) / (double)CLOCKS_PER_SEC;
	tempo_medio += time_in_seconds [k1];
	*/
	
	/*
	tempo_medio = tempo_medio/10000;

	printf ("%lf\n", tempo_medio);
	*/
	
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Critérios para a coordenação
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	for ( i = 0; i < Numero_barras; i++) 
	{
		if ( Tipo_coordenacao == 1 )           // Critério de coordenação: Icc trifásica 
		{
			I_coord [i] = Icc_3ph_As [i];
		}
		else if ( Tipo_coordenacao == 2 )     // Critério de coordenação: Icc monofásica 
		{
			I_coord [i] = Icc_1ph_As [i];
		}
		else if ( Tipo_coordenacao == 3 )     // Critério de coordenação: Icc máxima
		{
			I_coord [i] = Icc_max [i];
		}
		else
		{
			I_coord [i] = I_inrush [i];
		}
		//printf ("Icc_3ph = %4.1f Icc_1ph = %4.1f Icc_max = %4.1f Iinrush = %4.1f\n", Icc_3ph_As [i] * I_base, Icc_1ph_As [i] * I_base, Icc_max [i] * I_base, I_inrush [i]);
	}

	//------------------------------------------------------------------------------------------------------------------
    // Rotina de escrita dos dados no txt
    //------------------------------------------------------------------------------------------------------------------
    
    FILE * pFile;   
    pFile = fopen ("Resultado_Curto-circuito.txt","w"); 
    fprintf (pFile, "                                     Resultado do Curto-circuito\n");
    fprintf (pFile, " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  _ _ _ _ _ _ _  _ _ _ _ _ _ _ _ _ _ _ _ _ _  _ _ _ _ _ _ _  _ _ _ _ _ _ _ _ _  \n");
	fprintf (pFile, "|            |              |              |              |              |              |              |              |              |\n");
	fprintf (pFile, "| Barra ord  |   |Icc 3ph|  | |Icc 3ph As| |   |Icc 2ph|  | |Icc 2ph As| |   |Icc 1ph|  | |Icc 1ph As| | |Icc 1ph min | |Icc max     |\n");
    fprintf (pFile, "|_ _ _ _ _ _ | _ _ _ _ _ _ _|_ _ _ _ _ _ _ | _ _ _ _ _ _ _| _ _ _ _ _ _ _| _ _ _ _ _ _ _|_ _ _ _ _ _ _ |_ _ _ _ _ _ _ |_ _ _ _ _ _ _ |\n");
	fprintf (pFile, "|%12d|%14.5f|%14.5f|%14.5f|%14.5f|%14.5f|%14.5f|%14.5f|%14.5f|\n", 
	         BarraSub, Icc_3ph [0] * I_base, Icc_3ph_As [0] * I_base, Icc_2ph [0]* I_base, Icc_2ph_As [0]* I_base, Icc_1ph [0]* I_base, Icc_1ph_As [0]* I_base, Icc_1ph_min [0]* I_base, Icc_max [0]* I_base);

	 for (i = 1 ; i < Numero_barras ; i++)     
    {
	  fprintf (pFile, "|%12d|%14.5f|%14.5f|%14.5f|%14.5f|%14.5f|%14.5f|%14.5f|%14.5f|\n", 
	           Nj_renum [i-1], Icc_3ph [i] * I_base, Icc_3ph_As [i] * I_base, Icc_2ph [i]* I_base, Icc_2ph_As [i]* I_base, Icc_1ph [i]* I_base, Icc_1ph_As [i]* I_base, Icc_1ph_min [i]* I_base, Icc_max [i]* I_base); 
    }	   
    fprintf (pFile, "|_ _ _ _ _ _ | _ _ _ _ _ _ _|_ _ _ _ _ _ _ | _ _ _ _ _ _ _| _ _ _ _ _ _ _| _ _ _ _ _ _ _|_ _ _ _ _ _ _ |_ _ _ _ _ _ _ |_ _ _ _ _ _ _ |\n");
	fclose  (pFile                            );

}

void Calculo_do_fluxo::encontrar_pais_e_filhos ()
{
	//------------------------------------------------------------------------------------------------------------------
    // Iniciar valores da IndexStruct com 9999 (apenas como uma flag que não foi utilizada)
    //------------------------------------------------------------------------------------------------------------------

	for ( i = 0; i < Numero_linhas; i++)
	{
		IndexStruct [i] = 9999;
	}

	//------------------------------------------------------------------------------------------------------------------
    // Encontrar Pai e filhos
    //------------------------------------------------------------------------------------------------------------------

	// Aqui será tomado como premissa que os transformadores interligam apenas a rede primária com a secundária. Desta forma, suas proteções nunca serão pais

	FilhosCH FilhosCH_temp;
	FilhosDJ FilhosDJ_temp;
	int Aux1, Aux2;

	for ( i = Numero_linhas - 1 ; i > -1 ; i--)
	{	
		if ( Tipo_Circuito [IndexRamo [i]] == "DJ" || ( Tipo_Circuito [IndexRamo [i]] == "CH" && (Tipo_CH [IndexRamo [i]] == 0 || Tipo_CH [IndexRamo [i]] == 6) || Tipo_Circuito [IndexRamo [i]] == "TR")) // Compara se o elemento é uma Chave ou Disjuntor, se for CH, verifica se a mesma tem fusível ou religador ou um elo-fusível do Trafo
		{ 
			Aux1 = Ni_renum [i]; // Pai temporário
			Aux2 = i; // Filho procurado
			
			for (j = i -1; j > -1; j --)
			{
				if (Nj_renum [j] == Aux1) // "Caso a barra analisada tenha como Filho o Pai procurado"
				{
					if (Tipo_Circuito [IndexRamo [j]] == "DJ" || ( Tipo_Circuito [IndexRamo [j]] == "CH" && (Tipo_CH [IndexRamo [j]] == 0 || Tipo_CH [IndexRamo [j]] == 6))) //  Compara se o elemento é uma Chave ou Disjuntor, se for CH, verifica se a mesma tem fusível ou religador
					{
						if (Tipo_Circuito [IndexRamo [j]] == "CH") // Caso o elemento de proteção seja uma chave fusível ou religadora
						{
							for ( k = 0; k < CHAVEPROT.size (); k++) // Encontra na estrutura o elemento desejado e o atualiza
							{
								if (CHAVEPROT [k].Nj_renum == Nj_renum [j])
								{   
									FilhosCH_temp.Ramos_ord_FilhoCH = i;
									if ( Tipo_Circuito [IndexRamo [i]] == "CH" ) // Caso o filho seja uma chave fusível
									{
										printf ("CH -- pai ramo %d // CH Fusível -- filho ramo %d     struct = %d\n", j, i,k);
										FilhosCH_temp.TiposFilhosCH = "CH"; 
										FilhosCH_temp.TipoChave    =  Tipo_CH [IndexRamo [i]]; 
									}
									else if ( Tipo_Circuito [IndexRamo [i]] == "TR")
									{
										printf ("CH -- pai ramo %d // TR -- filho ramo %d\n", j, i);
										FilhosCH_temp.TipoChave    =  0; 
										FilhosCH_temp.TiposFilhosCH = "TR";
										
									}

									CHAVEPROT [k].STRUCTFILHOSCH.push_back (FilhosCH_temp);
									IndexStruct [j] = k; // Indice nas estruturas dos elementos de proteção que são pais
									break;
								}
							}
						}
						else // Caso o elemento de proteção seja um disjuntor
						{
							for ( k = 0; k < DISJUNTORPROT.size (); k++) // Encontra na estrutura o elemento desejado e o atualiza
							{
								if ( DISJUNTORPROT [k].Nj_renum == Nj_renum [j])
								{
									FilhosDJ_temp.Ramos_ord_FilhoDJ = i;
									
									if ( Tipo_Circuito [IndexRamo [i]] == "CH")
									{
										printf("DJ -- pai ramo %d // CH -- filho ramo %d\n", j, i);
										FilhosDJ_temp.TiposFilhosDJ = "CH";
										FilhosCH_temp.TipoChave    = Tipo_CH [IndexRamo [i]];

									}
									else if ( Tipo_Circuito [IndexRamo [i]] == "TR")
									{
										printf("DJ -- pai ramo %d // TR -- filho ramo %d\n", j, i);
										FilhosDJ_temp.TiposFilhosDJ = "TR";
									}
									else if ( Tipo_Circuito [IndexRamo [i]] == "DJ")
									{
										printf("DJ -- pai ramo %d // DJ -- filho ramo %d\n", j, i);
										FilhosDJ_temp.TiposFilhosDJ = "DJ";
									}
									DISJUNTORPROT [k].STRUCTFILHOSDJ.push_back (FilhosDJ_temp);
									IndexStruct [j] = k; // Indice nas estruturas dos elementos de proteção que são pais
									break;
								}
							}
						}
					}
					else // Caso o ramo no qual o Filho e o Pai procurado, o valor do pai é atualizado
					{
						Aux1 = Ni_renum [j]; // Pai novo temporário
					}
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------------------------
    // Alocando o IndexStruct na estrutura dos trafos
    //------------------------------------------------------------------------------------------------------------------

	for (i = 0; i < TRAFOS_DISTRI.size (); i++)
	{
		IndexStruct [TRAFOS_DISTRI[i].Ramo_ord] = i;
	}

	//------------------------------------------------------------------------------------------------------------------
    // Alocando auxiliar dos valores dos elos fusiveils
    //------------------------------------------------------------------------------------------------------------------

	V_aux = V_ref*sqrt(3.0);

	if ( V_aux <= 2300.0)
	{
		elo = 1;
	}
	else if ( V_aux <= 3800.0)
	{
		elo = 2;
	}
	else if ( V_aux <= 6600.0)
	{
		elo = 3;
	}
	else if (V_aux <= 11400.0)
	{
		elo = 4;
	}
	else if ( V_aux <= 13800.0)
	{
		elo = 5;
	}
	else if ( V_ref*sqrt(3.0) <= 22000.0)
	{
		elo = 6;
	}
	else if ( V_aux <= 25000.0)
	{
		elo = 7;
	}
	else if ( V_aux <= 34500.0)
	{
		elo = 8;
	}
	else
	{
		printf ("Fusível do trafo não suporta o nível de tensão\n");
	}
}

void Calculo_do_fluxo::alocacao_elos_fusiveis_trafos_novo (int indice)
{
	if (Tipo_sistema == 3) // Trifásico
		{
			switch (elo)
			{
				case 1: //2300V
					 if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo =  2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 6;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 8;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 10;
					 }				
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 45000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 12;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 50000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 12;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 75000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 20;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 100000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 25;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 112500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 30;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 150000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 40;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 200000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 50;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 225000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 50;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 250000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 65;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 300000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 80;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 400000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 100;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 500000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 100;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 600000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 140;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;

					 //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
					 case 2://3800V
					 if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 6;
					 }				
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 45000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 8;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 50000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 8;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 75000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 12;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 100000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 15;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 112500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 20;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 150000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 25;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 200000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 30;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 225000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 40;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 250000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 40;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 300000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 50;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 400000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 65;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 500000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 80;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 600000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 100;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;
					 
					 //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
					 case 3://6600V
					 if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }				
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 45000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 50000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 75000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 6;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 100000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 10;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 112500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 10;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 150000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 15;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 200000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 20;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 225000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 20;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 250000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 25;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 300000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 30;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 400000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 40;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 500000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 50;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 600000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 65;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;
					 
					 //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
					 case 4://11400V
					 if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;

					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }				
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 45000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 50000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 75000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 100000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 112500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 6;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 150000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 8;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 200000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 10;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 225000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 12;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 250000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 15;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 300000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 15;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 400000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 20;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 500000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 25;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 600000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 30;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;
					 
					 //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
					 case 5://13800V
					 if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }				
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 45000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 50000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 75000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 100000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 112500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 150000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 6;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 200000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 10;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 225000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 10;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 250000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 12;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 300000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 15;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 400000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 20;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 500000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 20;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 600000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 25;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;
					 
					 //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
					 case 6://22000V
					 if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }				
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 45000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 50000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 75000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 100000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 112500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 150000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 200000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 225000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 6;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 250000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 6;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 300000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 8;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 400000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 10;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 500000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 12;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 600000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 15;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;
					 
					 //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
					 case 7://25000V
					 if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }				
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 45000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 50000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 75000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 100000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 112500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 150000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 200000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 225000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 250000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 6;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 300000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 8;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 400000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 10;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 500000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 12;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 600000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 15;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;

					 //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
					 case 8://34500V
					 if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }				
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 45000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 50000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 75000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 100000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 112500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 150000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 200000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 225000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 250000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 300000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 400000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 8;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 500000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 10;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 600000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 12;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;

					 default:
					cout <<"\Opcao invalida!\n\n";
			}
	   }

	   if (Tipo_sistema == 1) // Monofásico
	   {
		   switch (elo)
			{
				case 1: //2300V
					 if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 3000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 7500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 6;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 12;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 15;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 20;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;

				case 2: //3800V
					if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 3000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 7500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 6;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 8;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 10;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;

				case 3: //6600V
					if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 3000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 7500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 5;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "K";
						TRAFOS_DISTRI[indice].ValorElo = 6;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;

				case 4: //11400V
					if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 3000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 7500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;

				case 5: //13800V
					if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 3000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 7500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 3;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;

				case 6: //22000V
					if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 3000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;						
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 7500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;

				case 7: //25000V
					if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 3000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1; 
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 7500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 2;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;

				case 8: //34500V
					if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 3000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 5000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 7500.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 10000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 15000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 25000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 30000.0)
					 {
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
						}
					 else if ( TRAFOS_DISTRI[indice].PotenciaTrafo <= 37500.0)
					 {						
						TRAFOS_DISTRI[indice].TipoElo  = "H";
						TRAFOS_DISTRI[indice].ValorElo = 1;
					 }
					 else
					 {
						 printf("Potencia do trafo nao suportada\n");
					 }
					 break;

				default:
					cout <<"Opcao invalida!\n\n";
			}
		}		
	
	//------------------------------------------------------------------------------------------------------------------
    // Encontra os tipos de fusíveis na strutura de CHAVEPROT e adiciona a flag "TR"
    //------------------------------------------------------------------------------------------------------------------

	for ( i1 = 0; i1 < CHAVEPROT.size (); i1++)
	{
		for ( j1 = 0; j1 < CHAVEPROT [i1].STRUCTFILHOSCH.size (); j1++)
		{
			 if (CHAVEPROT [i1].STRUCTFILHOSCH [j1].TiposFilhosCH == "TR") // Verifica se a estrutra é um elo fusível de um transformador
			 {
				 CHAVEPROT [i1].STRUCTFILHOSCH [j1].TipoEloFilhoCH = TRAFOS_DISTRI [IndexStruct [CHAVEPROT [i1].STRUCTFILHOSCH [j1].Ramos_ord_FilhoCH]].TipoElo;
				 CHAVEPROT [i1].STRUCTFILHOSCH [j1].ValorElo       = TRAFOS_DISTRI [IndexStruct [CHAVEPROT [i1].STRUCTFILHOSCH [j1].Ramos_ord_FilhoCH]].ValorElo;
			 }
		}
	}
}

void Calculo_do_fluxo::alocacao_elos_fusiveis_retaguarda_trafos (int indice)
{
	for ( j = 0; j < CHAVEPROT [IndexStruct [indice]].STRUCTFILHOSCH.size (); j++)
			{
				if ( CHAVEPROT [IndexStruct [indice]].STRUCTFILHOSCH [j].TiposFilhosCH == "TR") // Verifica se o filho é um elo-fusível de um transformador
				{
					I_coord_filho = I_coord [CHAVEPROT [IndexStruct [indice]].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH] * I_base; // Corrente máxima no filho analisado
					printf ("Elo min       = %d    Ramo = %d\n", CHAVEPROT [IndexStruct [indice]].ValorElo, indice);
					if  (CHAVEPROT [IndexStruct [indice]].STRUCTFILHOSCH [j].TipoEloFilhoCH == "H")
					{
						switch (CHAVEPROT [IndexStruct [indice]].STRUCTFILHOSCH [j].ValorElo) // Valor do elo do filho (transformador)
						{
							case 1:
								if (Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 280.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 10) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 10;
										}
									}
								
									else if ( I_coord_filho <= 510.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 15) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 15;
										}
									}
								
									else if ( I_coord_filho <= 840.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 25) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 25;
										}
									}
								
									else if ( I_coord_filho <= 1350.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 40) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
										}
									}
									else if ( I_coord_filho <= 2200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 65) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
										}
									}
									else if ( I_coord_filho <= 3900.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else // Fusíveis não preferenciais
								{
									if ( I_coord_filho <= 125.0) // Verifica o valor da Icc máxima na qual o filho esta submetido
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 8) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 8;
										}
									}
									else if ( I_coord_filho <= 380.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 12) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{ 
											CHAVEPROT [IndexStruct [indice]].ValorElo = 12;
										}
									}
									else if ( I_coord_filho <= 650.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 20) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 20;
										}
									}
									else if ( I_coord_filho <= 1060.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 30) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
										}
									}
									else if ( I_coord_filho <= 1700.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 50) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
										}
									}
									else if ( I_coord_filho <= 2800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 80) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 2:
								if ( Elo_Preferencial ==  "Sim")
								{
									if ( I_coord_filho <= 45.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 10) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 10;
										}
									}
									else if ( I_coord_filho <= 450.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 15) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 15;
										}
									}
									else if ( I_coord_filho <= 840.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 25) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 25;
										}
									}
									else if ( I_coord_filho <= 1350.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 40) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
										}
									}
									else if ( I_coord_filho <= 2200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 65) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
										}
									}
									else if ( I_coord_filho <= 3900.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else // Elo-fusível não preferencial
								{
									if ( I_coord_filho <= 220.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 12) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 12;
										}
									}
									else if ( I_coord_filho <= 650.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 20) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 20;
										}
									}
									else if ( I_coord_filho <= 1060.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 30) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
										}
									}
									else if ( I_coord_filho <= 1700.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 50) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
										}
									}
									else if ( I_coord_filho <= 2800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 80) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 3:
								if (Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 45.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 10) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 10;
										}
									}
									else if ( I_coord_filho <= 450.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 15) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 15;
										}
									}
									else if ( I_coord_filho <= 840.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 25) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 25;
										}
									}
									else if ( I_coord_filho <= 1350.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 40) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
										}
									}
									else if ( I_coord_filho <= 2200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 65) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
										}
									}
									else if ( I_coord_filho <= 3900.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{
									if ( I_coord_filho <= 220.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 12) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 12;
										}
									}
									else if ( I_coord_filho <= 650.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 20) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 20;
										}
									}
									else if ( I_coord_filho <= 1060.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 30) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
										}
									}
									else if ( I_coord_filho <= 1700.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 50) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
										}
									}
									else if ( I_coord_filho <= 2800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 80) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 5:
								if ( Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 45.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 10) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 10;
										}
									}
									else if ( I_coord_filho <= 220.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 12) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 12;
										}
									}
									else if ( I_coord_filho <= 450.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 15) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 15;
										}
									}
									else if ( I_coord_filho <= 840.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 25) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 25;
										}
									}
									else if ( I_coord_filho <= 1350.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 40) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
										}
									}
									else if ( I_coord_filho <= 2200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 65) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
										}
									}
									else if ( I_coord_filho <= 3900.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{								
									if ( I_coord_filho <= 220.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 12) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 12;
										}
									}
									else if ( I_coord_filho <= 650.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 20) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 20;
										}
									}
									else if ( I_coord_filho <= 1060.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 30) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
										}
									}
									else if ( I_coord_filho <= 1700.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 50) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
										}
									}
									else if ( I_coord_filho <= 2800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 80) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 6:
								if ( Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 190.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 10) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 10;
										}
									}
									else if ( I_coord_filho <= 510.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 15) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 15;
										}
									}
									else if ( I_coord_filho <= 840.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 25) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 25;
										}
									}
									else if ( I_coord_filho <= 1340.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 40) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
										}
									}
									else if ( I_coord_filho <= 2200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 65) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
										}
									}
									else if ( I_coord_filho <= 3900.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{
									if ( I_coord_filho <= 350.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 12) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 12;
										}
									}
									else if ( I_coord_filho <= 650.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 20) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 20;
										}
									}
									else if ( I_coord_filho <= 1060.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 30) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
										}
									}
									else if ( I_coord_filho <= 1700.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 50) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
										}
									}
									else if ( I_coord_filho <= 2800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 80) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 8:
								if ( Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 440.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 15) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 15;
										}
									}
									else if ( I_coord_filho <= 840.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 25) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 25;
										}
									}
									else if ( I_coord_filho <= 1340.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 40) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
										}
									}
									else if ( I_coord_filho <= 2200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 65) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
										}
									}
									else if ( I_coord_filho <= 3900.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{
									if ( I_coord_filho <= 210.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 12) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 12;
										}
									}
									else if ( I_coord_filho <= 650.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 20) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 20;
										}
									}
									else if ( I_coord_filho <= 1060.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 30) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
										}
									}
									else if ( I_coord_filho <= 1700.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 50) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
										}
									}
									else if ( I_coord_filho <= 2800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 80) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 10:
								if ( Elo_Preferencial == "Sim" )
								{
									if ( I_coord_filho <= 300.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 15) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 15;
										}
									}
									else if ( I_coord_filho <= 840.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 25) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 25;
										}
									}
									else if ( I_coord_filho <= 1340.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 40) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
										}
									}
									else if ( I_coord_filho <= 2200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 65) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
										}
									}
									else if ( I_coord_filho <= 3900.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{
									if ( I_coord_filho <= 540.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 20) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 20;
										}
									}
									else if ( I_coord_filho <= 1060.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 30) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
										}
									}
									else if ( I_coord_filho <= 1700.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 50) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
										}
									}
									else if ( I_coord_filho <= 2800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 80) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 12:
								if ( Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 710.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 25) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 25;
										}
									}
									else if ( I_coord_filho <= 1340.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 40) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
										}
									}
									else if ( I_coord_filho <= 2200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 65) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
										}
									}
									else if ( I_coord_filho <= 3900.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{
									if ( I_coord_filho <= 320.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 20) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 20;
										}
									}
									else if ( I_coord_filho <= 1050.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 30) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
										}
									}
									else if ( I_coord_filho <= 1700.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 50) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
										}
									}
									else if ( I_coord_filho <= 2800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 80) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 15:
								if ( Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 430.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 25) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 25;
										}
									}
									else if ( I_coord_filho <= 1340.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 40) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
										}
									}
									else if ( I_coord_filho <= 2200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 65) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
										}
									}
									else if ( I_coord_filho <= 3900.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{
									if ( I_coord_filho <= 870.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 30) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
										}
									}
									else if ( I_coord_filho <= 1700.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 50) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
										}
									}
									else if ( I_coord_filho <= 2800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 80) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 20:
								if ( Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 1100.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 40) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
										}
									}
									else if ( I_coord_filho <= 2200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 65) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
										}
									}
									else if ( I_coord_filho <= 3900.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{
									if ( I_coord_filho <= 500.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 30) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
										}
									}
									else if ( I_coord_filho <= 1700.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 50) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
										}
									}
									else if ( I_coord_filho <= 2800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 80) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 25:
								if ( Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 660.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 40) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
										}
									}
									else if ( I_coord_filho <= 2200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 65) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
										}
									}
									else if ( I_coord_filho <= 3900.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{
									if ( I_coord_filho <= 1350.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 50) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
										}
									}
									else if ( I_coord_filho <= 2800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 80) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 30:
								if ( Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 1350.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 65) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
										}
									}
									else if ( I_coord_filho <= 3900.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{
									if ( I_coord_filho <= 850.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 50) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
										}
									}
									else if ( I_coord_filho <= 2800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 80) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 40:
								if ( Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 1100.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 65) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
										}
									}
									else if ( I_coord_filho <= 3900.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{
									if ( I_coord_filho <= 2200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 80) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 50:
								if ( Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 3500.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{
									if ( I_coord_filho <= 1450.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 80) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 65:
								if ( Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 2400.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 100) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
										}
									}
									else if ( I_coord_filho <= 5800.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{ 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 80:
								if ( Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 4500.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9200.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 100:
								if ( Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 2000.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 140) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
										}
									}
									else if ( I_coord_filho <= 9100.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 140:
								if ( Elo_Preferencial == "Sim")
								{
									if ( I_coord_filho <= 4000.0)
									{
										if (CHAVEPROT [IndexStruct [indice]].ValorElo < 200) // Modifica apenas se o valor do fusível pai for menor do que o necessário para a coordenação
										{
											CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
										}
									}
									else 
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								else
								{
									{
										printf (" Icc muito alta, seletividade não é garantida \n");
									}
								}
								break;

							case 200:
								printf ("Erro, não é possível obter a seletividade entre fusível-fusível de 200k\n");
								break;

							default:
								printf ("Fusível não suportado, verificar código\n");
						}  // Finaliza o switch
					} 
					
					else if (CHAVEPROT [IndexStruct [indice]].STRUCTFILHOSCH [j].TipoEloFilhoCH == "K")
					{
						switch (CHAVEPROT [IndexStruct [indice]].STRUCTFILHOSCH [j].ValorElo)   
						{
						case 6: // Fusivel Protetor de 6K 
							if ( Elo_Preferencial == "Sim")
							{
								if ( I_coord_filho <= 510.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 15;
								}
								else if ( I_coord_filho <= 840.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 25;
								}
								else if ( I_coord_filho <= 1340.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
								}
								else if ( I_coord_filho <= 2200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
								}
								else if ( I_coord_filho <= 3900.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
								}
								else if ( I_coord_filho <= 5800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
								}
								else if ( I_coord_filho <= 9200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 200K) \n");
								}
							}
							else
								{
									if (I_coord_filho <= 350.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 12;
								}
								else if ( I_coord_filho <= 650.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 20;
								}
								else if ( I_coord_filho <= 1060.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
								}
								else if ( I_coord_filho <= 1700.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
								}					
								else if ( I_coord_filho <= 2800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
								}
								{
								printf ("Fusivel protegido não suportado (maior que 80K) \n");
								}
							}
							break;		

						case 8: // Fusivel Protetor de 8K
							if ( Elo_Preferencial == "Sim")
							{
								if ( I_coord_filho <= 440.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 15;
								}
								else if ( I_coord_filho <= 840.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 25;
								}
								else if ( I_coord_filho <= 1340.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
								}
								else if ( I_coord_filho <= 2200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
								}
								else if ( I_coord_filho <= 3900.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
								}
								else if ( I_coord_filho <= 5800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
								}
								else if ( I_coord_filho <= 9200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 200K) \n");
								}
							}
							else
							{
								if (I_coord_filho <= 210.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 12;
								}
								else if ( I_coord_filho <= 650.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 20;
								}
								else if ( I_coord_filho <= 1060.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
								}
								else if ( I_coord_filho <= 1700.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
								}
								else if ( I_coord_filho <= 2800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
								}
								else
								{
									printf ("Fusivel protegido não suportado (maior que 80K) \n");
								}
							}
							break;	

						case 10: // Fusivel Protetor de 10K
							if ( Elo_Preferencial == "Sim")
							{
								if ( I_coord_filho <= 300.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 15;
								}
								else if ( I_coord_filho <= 840.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 25;
								}
								else if ( I_coord_filho <= 1340.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
								}
								else if ( I_coord_filho <= 2200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
								}
								else if ( I_coord_filho <= 3900.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
								}
								else if ( I_coord_filho <= 5800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
								}
								else if ( I_coord_filho <= 9200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 200K) \n");
								}
							}
							else
							{
								if ( I_coord_filho <= 540.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 20;
								}
								else if ( I_coord_filho <= 1060.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
								}
								else if ( I_coord_filho <= 1700.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
								}
								else if ( I_coord_filho <= 2800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
								}
								else
								{
									printf ("Fusivel protegido não suportado (maior que 80K) \n");
								}
							}				
							break;	

						case 12: // Fusivel Protetor de 12K
							if ( Elo_Preferencial == "Sim")
							{
								if ( I_coord_filho <= 710.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 25;
								}
								else if ( I_coord_filho <= 1340.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
								}
								else if ( I_coord_filho <= 2200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
								}
								else if ( I_coord_filho <= 3900.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
								}
								else if ( I_coord_filho <= 5800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
								}
								else if ( I_coord_filho <= 9200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 200K) \n");
								}
							}
							else
							{
								if ( I_coord_filho <= 320.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 20;
								}
								else if ( I_coord_filho <= 1050.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
								}
								else if ( I_coord_filho <= 1700.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
								}
								else if ( I_coord_filho <= 2800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 80K) \n");
								}
							}
							break;		

						case 15: // Fusivel Protetor de 15K
							if ( Elo_Preferencial == "Sim")
							{
								if ( I_coord_filho <= 430.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 25;
								}
								else if ( I_coord_filho <= 1340.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
								}
								else if ( I_coord_filho <= 2200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
								}
								else if ( I_coord_filho <= 3900.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
								}
								else if ( I_coord_filho <= 5800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
								}
								else if ( I_coord_filho <= 9200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 200K) \n");
								}
							}
							else
							{
								if ( I_coord_filho <= 870.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
								}
								else if ( I_coord_filho <= 1700.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
								}
								else if ( I_coord_filho <= 2800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 80K) \n");
								}
							}
							break;	

						case 20: // Fusivel Protetor de 20K
							if ( Elo_Preferencial == "Sim")
							{
								if ( I_coord_filho <= 1100.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
								}
								else if ( I_coord_filho <= 2200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
								}
								else if ( I_coord_filho <= 3900.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
								}
								else if ( I_coord_filho <= 5800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
								}
								else if ( I_coord_filho <= 9200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 200K) \n");
								}
							}
							else
							{
								if ( I_coord_filho <= 500.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 30;
								}					
								else if ( I_coord_filho <= 1700.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
								}
								else if ( I_coord_filho <= 2800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
								}
								else
								{
									printf ("Fusivel protegido não suportado (maior que 80K) \n");
								}
							}
							break;

						case 25: // Fusivel Protetor de 25K
							if ( Elo_Preferencial == "Sim")
							{
								if ( I_coord_filho <= 660.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 40;
								}
								else if ( I_coord_filho <= 2200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
								}
								else if ( I_coord_filho <= 3900.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
								}
								else if ( I_coord_filho <= 5800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
								}
								else if ( I_coord_filho <= 9200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 200K) \n");
								}
							}
							else
							{
								if ( I_coord_filho <= 1350.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
								}
								else if ( I_coord_filho <= 2800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 80K) \n");
								}
							}
							break;	

						case 30: // Fusivel Protetor de 30K
							if ( Elo_Preferencial == "Sim")
							{
								if ( I_coord_filho <= 1700.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
								}
								else if ( I_coord_filho <= 3900.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
								}
								else if ( I_coord_filho <= 5800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
								}
								else if ( I_coord_filho <= 9200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 200K) \n");
								}
							}
							else
							{
								if ( I_coord_filho <= 850.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 50;
								}					
								else if ( I_coord_filho <= 2800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 80K) \n");
								}
							}
							break;	

						case 40: // Fusivel Protetor de 40K
							if ( Elo_Preferencial == "Sim")
							{
								if ( I_coord_filho <= 1100.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 65;
								}
								else if ( I_coord_filho <= 3900.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
								}
								else if ( I_coord_filho <= 5800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
								}
								else if ( I_coord_filho <= 9200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 200K) \n");
								}
							}
							else
							{						
								if ( I_coord_filho <= 2200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 80K) \n");
								}
							}
							break;	

						case 50: // Fusivel Protetor de 50K
							if ( Elo_Preferencial == "Sim")
							{
								if ( I_coord_filho <= 3500.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
								}
								else if ( I_coord_filho <= 5800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
								}
								else if ( I_coord_filho <= 9200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 200K) \n");
								}
							}
							else
							{
								if ( I_coord_filho <= 1450.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 80;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 80K) \n");
								}
							}
							break;		

						case 65: // Fusivel Protetor de 65K
							if ( Elo_Preferencial == "Sim")
							{
								if ( I_coord_filho <= 2400.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 100;
								}
								else if ( I_coord_filho <= 5800.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
								}
								else if ( I_coord_filho <= 9200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 200K) \n");
								}
							}
							else
							{
								printf ("Fusivel protegido não suportado (maior que 80K) \n");
							}
							break;	

						case 80: // Fusivel Protetor de 80K
							if ( Elo_Preferencial == "Sim")
							{
								if ( I_coord_filho <= 4500.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
								}
								else if ( I_coord_filho <= 9200.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 200K) \n");
								}
							}
							else
							{
								printf ("Fusivel protegido não suportado (maior que 80K) \n");
							}
							break;

						case 100: // Fusivel Protetor de 100K
							if ( Elo_Preferencial == "Sim")
							{
								if ( I_coord_filho <= 2000.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 140;
								}
								else if ( I_coord_filho <= 9100.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 200;

								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 200K) \n");
								}
							}
							else
							{
								printf ("Fusivel protegido não suportado (maior que 80K) \n");
							}
							break;

						case 140: // Fusivel Protetor de 140K
							if ( Elo_Preferencial == "Sim")
							{
								if ( I_coord_filho <= 4000.0)
								{
									CHAVEPROT [IndexStruct [indice]].TipoElo  = "K";
									CHAVEPROT [IndexStruct [indice]].ValorElo = 200;
								}
								else
								{
								printf ("Fusivel protegido não suportado (maior que 200K) \n");
								}
							}
							else
							{
								printf ("Fusivel protegido não suportado (maior que 80K) \n");
							}
							break;
						default:
							printf ("Fusivel invalido\n");
						}
					}
					
					printf ("Elo novo      = %d    Ramo = %d\n", CHAVEPROT [IndexStruct [indice]].ValorElo, indice);
					printf ("FusIvel filho = %d%s    Icc  = %f\n", CHAVEPROT [IndexStruct [indice]].STRUCTFILHOSCH [j].ValorElo,CHAVEPROT [IndexStruct [indice]].STRUCTFILHOSCH [j].TipoEloFilhoCH.c_str (), I_coord_filho);
					printf ("------------------------------------------------------\n");
				}      // Finaliza a verificação se o filho é um trafo
			}          // Finaliza o for que varre os filhos

}

void Calculo_do_fluxo::verifica_amperagem_fusivel (int indice)
{	
		Aux_I_elo = CHAVEPROT [indice].Icarga;
		
		if (CHAVEPROT [indice].TipoCH == 0)     // Verifica se o dispostivo de proteção é uma chave elo-fusível
		{
			if (Elo_Preferencial == "Sim") // Verifica se os fusíveis são preferenciais
			{
				if (Aux_I_elo < 6.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;

				}
				else if (Aux_I_elo < 10.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;
				}
				else if (Aux_I_elo < 15.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;
				}
				else if (Aux_I_elo < 25.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;
				}
				else if (Aux_I_elo < 40.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;
				}
				else if (Aux_I_elo < 65.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;
				}
				else if (Aux_I_elo < 100.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;
				}
				else if (Aux_I_elo < 140.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;
				}
				else if (Aux_I_elo < 200.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;
				}
				else
				{
					CHAVEPROT [indice].TipoElo = "I excede o max";
				}
			}
			else
			{
				if (Aux_I_elo < 8.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;
				}
				else if (Aux_I_elo < 12.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;
				}
				else if (Aux_I_elo < 20.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;
				}
				else if (Aux_I_elo < 30.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;
				}
				else if (Aux_I_elo < 50.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;
				}
				else if (Aux_I_elo < 80.0)
				{
					CHAVEPROT [indice].TipoElo  = "K";
					CHAVEPROT [indice].ValorElo = 6;
				}
				else
				{
					CHAVEPROT [indice].TipoElo = "I excede o max";
				}
		}
	}
}

void Calculo_do_fluxo::coordenacao_entre_elos_fusiveis (int indice)
{
	ValorElo_Protetor_K = 0;                                                                      // Inicia/Reseta o Valor da auxiliar em zero
																								         
	for (j = 0; j < CHAVEPROT [IndexStruct [indice]].STRUCTFILHOSCH.size (); j++)                      // Começa a busca dos filhos
	{																					         
		if ( CHAVEPROT [IndexStruct [indice]].STRUCTFILHOSCH [j].TiposFilhosCH == "CH")                // Verifica se o fusivel filho é uma chave (não trafo, pois estes já estao coordenados)
		{
			Ramo_Fusivel_Protetor = CHAVEPROT [IndexStruct [indice]].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH;

			if ( CHAVEPROT [IndexStruct [Ramo_Fusivel_Protetor]].ValorElo > ValorElo_Protetor_K ) // Busca pelo filho com fusível de maior valor
			{
				ValorElo_Protetor_K = CHAVEPROT [IndexStruct [Ramo_Fusivel_Protetor]].ValorElo;   // Atualiza o valor da variável auxiliar para o maior fusível filho
			}
		} 
	} // Termina o for do contador j;

	pai   = IndexStruct [indice];
	printf ("Fusivel protegido (retaguarda) = %d%s   - Ramo  %d\n", CHAVEPROT [pai].ValorElo, CHAVEPROT [pai].TipoElo.c_str(), indice);

	if  ( ValorElo_Protetor_K != 0 )   // Caso o valor desta variável auxiliar for diferente que 0, significa que o programa encontrou um pai cujos filhos não são trafos
		{                              // visto que estes já foram coordenados
		switch (ValorElo_Protetor_K)   // De acordo com o maior fusível protetor
		{
		case 6: // Fusivel Protetor de 6K 
			if ( Elo_Preferencial == "Sim")
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 510.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 15;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 840.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 25;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1340.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 40;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 65;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 3900.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 100;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 5800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 140;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 9200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 200;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 200K) \n");
				}
			}
			else
				{
					if (I_coord [Ramo_Fusivel_Protetor] <= 350.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 12;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 650.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 20;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1060.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 30;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1700.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 50;
				}					
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 80;
				}
				{
				printf ("Fusivel protegido não suportado (maior que 80K) \n");
				}
			}
			break;		

		case 8: // Fusivel Protetor de 8K
			if ( Elo_Preferencial == "Sim")
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 440.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 15;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 840.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 25;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1340.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 40;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 65;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 3900.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 100;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 5800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 140;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 9200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 200;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 200K) \n");
				}
			}
			else
			{
				if (I_coord [Ramo_Fusivel_Protetor] <= 210.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 12;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 650.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 20;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1060.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 30;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1700.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 50;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 80;
				}
				else
				{
					printf ("Fusivel protegido não suportado (maior que 80K) \n");
				}
			}
			break;	

		case 10: // Fusivel Protetor de 10K
			if ( Elo_Preferencial == "Sim")
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 300.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 15;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 840.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 25;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1340.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 40;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 65;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 3900.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 100;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 5800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 140;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 9200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 200;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 200K) \n");
				}
			}
			else
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 540.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 20;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1060.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 30;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1700.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 50;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 80;
				}
				else
				{
					printf ("Fusivel protegido não suportado (maior que 80K) \n");
				}
			}				
			break;	

		case 12: // Fusivel Protetor de 12K
			if ( Elo_Preferencial == "Sim")
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 710.0)
				{
					CHAVEPROT [pai].TipoElo = "K";
					CHAVEPROT [pai].ValorElo = 25;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1340.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 40;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 65;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 3900.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 100;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 5800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 140;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 9200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 200;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 200K) \n");
				}
			}
			else
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 320.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 20;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1050.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 30;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1700.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 50;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 80;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 80K) \n");
				}
			}
			break;		

		case 15: // Fusivel Protetor de 15K
			if ( Elo_Preferencial == "Sim")
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 430.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 25;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1340.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 40;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 65;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 3900.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 100;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 5800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 140;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 9200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 200;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 200K) \n");
				}
			}
			else
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 870.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 30;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1700.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 50;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 80;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 80K) \n");
				}
			}
			break;	

		case 20: // Fusivel Protetor de 20K
			if ( Elo_Preferencial == "Sim")
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 1100.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 40;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 65;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 3900.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 100;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 5800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 140;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 9200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 200;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 200K) \n");
				}
			}
			else
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 500.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 30;
				}					
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 1700.0)
				{
					CHAVEPROT [pai].TipoElo = "K";
					CHAVEPROT [pai].ValorElo = 50;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 80;
				}
				else
				{
					printf ("Fusivel protegido não suportado (maior que 80K) \n");
				}
			}
			break;

		case 25: // Fusivel Protetor de 25K
			if ( Elo_Preferencial == "Sim")
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 660.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 40;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 65;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 3900.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 100;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 5800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 140;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 9200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 200;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 200K) \n");
				}
			}
			else
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 1350.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 50;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 80;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 80K) \n");
				}
			}
			break;	

		case 30: // Fusivel Protetor de 30K
			if ( Elo_Preferencial == "Sim")
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 1700.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 65;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 3900.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 100;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 5800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 140;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 9200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 200;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 200K) \n");
				}
			}
			else
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 850.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 50;
				}					
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 2800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 80;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 80K) \n");
				}
			}
			break;	

		case 40: // Fusivel Protetor de 40K
			if ( Elo_Preferencial == "Sim")
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 1100.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 65;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 3900.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 100;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 5800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 140;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 9200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 200;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 200K) \n");
				}
			}
			else
			{						
				if ( I_coord [Ramo_Fusivel_Protetor] <= 2200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 80;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 80K) \n");
				}
			}
			break;	

		case 50: // Fusivel Protetor de 50K
			if ( Elo_Preferencial == "Sim")
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 3500.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 100;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 5800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 140;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 9200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 200;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 200K) \n");
				}
			}
			else
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 1450.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 80;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 80K) \n");
				}
			}
			break;		

		case 65: // Fusivel Protetor de 65K
			if ( Elo_Preferencial == "Sim")
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 2400.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 100;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 5800.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 140;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 9200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 200;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 200K) \n");
				}
			}
			else
			{
				printf ("Fusivel protegido não suportado (maior que 80K) \n");
			}
			break;	

		case 80: // Fusivel Protetor de 80K
			if ( Elo_Preferencial == "Sim")
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 4500.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 140;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 9200.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 200;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 200K) \n");
				}
			}
			else
			{
				printf ("Fusivel protegido não suportado (maior que 80K) \n");
			}
			break;

		case 100: // Fusivel Protetor de 100K
			if ( Elo_Preferencial == "Sim")
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 2000.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 140;
				}
				else if ( I_coord [Ramo_Fusivel_Protetor] <= 9100.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 200;

				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 200K) \n");
				}
			}
			else
			{
				printf ("Fusivel protegido não suportado (maior que 80K) \n");
			}
			break;

		case 140: // Fusivel Protetor de 140K
			if ( Elo_Preferencial == "Sim")
			{
				if ( I_coord [Ramo_Fusivel_Protetor] <= 4000.0)
				{
					CHAVEPROT [pai].TipoElo  = "K";
					CHAVEPROT [pai].ValorElo = 200;
				}
				else
				{
				printf ("Fusivel protegido não suportado (maior que 200K) \n");
				}
			}
			else
			{
				printf ("Fusivel protegido não suportado (maior que 80K) \n");
			}
			break;
		default:
			printf ("Fusivel invalido\n");
		}  // Finaliza o Switch
	}      // Finaliza o if

    printf ("NOVO\n");
    printf ("Fusivel protegido (retaguarda) = %d%s   - Ramo  %d\n", CHAVEPROT [pai].ValorElo, CHAVEPROT [pai].TipoElo.c_str(), indice);
	printf ("-------------------------------------------------\n");
}

void Calculo_do_fluxo::seletividade_elos_fusiveis_k_novo ()
{
	Elo_Preferencial = "Sim"; // Escolhe se os fusíveis utilizados serão preferenciais ou não preferenciais

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Seletividade fusivel-fusível
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	for ( i = Numero_linhas -1 ; i > -1 ; i--)
	{
		if ( Tipo_Circuito [ IndexRamo [i] ] == "TR") 
		{
			alocacao_elos_fusiveis_trafos_novo  (IndexStruct [i]); // Começa a aolocar os fusíveis dos transformadores
			I_inrush [i] += 8.0 * TRAFOS_DISTRI [ IndexStruct [i]].PotenciaTrafo / (sqrt (3.0) * TRAFOS_DISTRI [ IndexStruct [i]].TensaoPrim); // Calculo das correntes Inrush
			I_carga  [i] =        TRAFOS_DISTRI [ IndexStruct [i]].PotenciaTrafo / (sqrt (3.0) * TRAFOS_DISTRI [ IndexStruct [i]].TensaoPrim); // Calculo das correntes Icarga
		}
		else if ( IndexStruct [i] != 9999 && Tipo_CH [IndexRamo [i]] == 0 ) // Encontra chaves elo fusível do tipo Pai    
		{
			verifica_amperagem_fusivel               (IndexStruct [i]);
			alocacao_elos_fusiveis_retaguarda_trafos (i);
			coordenacao_entre_elos_fusiveis          (i);			
		}
		I_inrush [Ni_renum [i] - 1] += I_inrush [i]; // Calculo das correntes Inrush
		I_carga  [Ni_renum [i] - 1] += I_carga  [i]; // Calculo das correntes Icarga
	} // Finaliza o for i
	
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Quantidade_de_DJ = 0;

	for ( i = 0; i < CHAVEPROT.size (); i++ ) // Adiciona na estrutura CHAVEPROT
	{
		CHAVEPROT [i].Iinrush = I_inrush [CHAVEPROT [i].Ramo_ord];

		if (Modo_calculo_I_carga == 1) // Cálculo da corrente de carga via capacidade dos trafos
		{
			CHAVEPROT[i].Icarga = I_carga [CHAVEPROT[i].Ramo_ord];
		}
		else // Caso seja pelas correntes de curto circuito
		{
			CHAVEPROT[i].Icarga = I_carga_max [CHAVEPROT[i].Ramo_ord];
		}
	}
	for ( i = 0; i < DISJUNTORPROT.size (); i++ ) // Adiciona na estrutura DISJUNTORPROT
	{
		DISJUNTORPROT [i].Iinrush = I_inrush [DISJUNTORPROT [i].Ramo_ord];

		if (Modo_calculo_I_carga == 1) // Cálculo da corrente de carga via capacidade dos trafos
		{
			DISJUNTORPROT[i].Icarga = I_carga [DISJUNTORPROT[i].Ramo_ord];
		}
		else // Caso seja pelas correntes de curto circuito
		{
			DISJUNTORPROT[i].Icarga = I_carga_max [DISJUNTORPROT[i].Ramo_ord];
		}
	}

for (i = 0; i < CHAVEPROT.size (); i++)
{
	if (CHAVEPROT[i].STRUCTFILHOSCH.size () == 0)//Caso o fusível não tenha filhos...coloca o menor fusível conhecido
	{
		CHAVEPROT[i].TipoElo = "K";
		CHAVEPROT[i].ValorElo = 6;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Acrescenta os valores dos fusíveis TR e CH na estrutura dos Disjuntores
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

for (i = 0; i < DISJUNTORPROT.size (); i++)
{
	for (j = 0; j < DISJUNTORPROT[i].STRUCTFILHOSDJ.size (); j++)
	{
		DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Coordenado = "Sim";//Inicializa
		DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Coordenado_neutro = "Sim";

		if (DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "TR")
		{
			DISJUNTORPROT[i].STRUCTFILHOSDJ[j].ValorElo = TRAFOS_DISTRI[IndexStruct[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Ramos_ord_FilhoDJ]].ValorElo;
			DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TipoEloFilhoDJ = TRAFOS_DISTRI[IndexStruct[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Ramos_ord_FilhoDJ]].TipoElo;
		}
		else if (DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "CH")
		{
			for (k = 0; k < CHAVEPROT.size (); k++)
			{
				if (CHAVEPROT[k].Ramo_ord == DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Ramos_ord_FilhoDJ)
				{
					DISJUNTORPROT[i].STRUCTFILHOSDJ[j].ValorElo = CHAVEPROT[k].ValorElo;
					DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TipoEloFilhoDJ = CHAVEPROT[k].TipoElo;
					DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TipoChave = CHAVEPROT[k].TipoCH;
				}
			}
		}

	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Cria o IndexStructCH e IndexStructDJ
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
IndexStructCH = new int[Numero_linhas];
IndexStructDJ = new int[Numero_linhas];

for (i = 0; i < Numero_linhas; i++)
{
	IndexStructCH[i] = 9999;
	IndexStructDJ[i] = 9999;
}

for (i = 0; i < CHAVEPROT.size (); i++)
{
	IndexStructCH[CHAVEPROT[i].Ramo_ord] = i;
}

for (i = 0; i < DISJUNTORPROT.size (); i++)
{
	IndexStructDJ[DISJUNTORPROT[i].Ramo_ord] = i;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Atualiza os valores dos fusíves nas estruturas filhos
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
int aux_posicao;
for (i = 0; i < CHAVEPROT.size (); i++)
{
	for (j = 0; j < CHAVEPROT[i].STRUCTFILHOSCH.size (); j++)
	{
		CHAVEPROT[i].STRUCTFILHOSCH[j].Coordenado = "Sim"; // Atualiza o valor do elo nos filhos.
		CHAVEPROT[i].STRUCTFILHOSCH[j].Coordenado_neutro = "Sim"; // Atualiza o valor do elo nos filhos.

		if (CHAVEPROT[i].STRUCTFILHOSCH[j].TipoChave == 0 && CHAVEPROT[i].STRUCTFILHOSCH[j].TiposFilhosCH == "CH") // caso o filho seja uma chave fusível...
		{
			aux_posicao = IndexStructCH[CHAVEPROT[i].STRUCTFILHOSCH[j].Ramos_ord_FilhoCH];
			CHAVEPROT[i].STRUCTFILHOSCH[j].ValorElo = CHAVEPROT[aux_posicao].ValorElo; // Atualiza o valor do elo nos filhos
			CHAVEPROT[i].STRUCTFILHOSCH[j].TipoEloFilhoCH = CHAVEPROT[aux_posicao].TipoElo; // Atualiza o valor do elo nos filhos				
		}
	}
}

} // Finaliza a função 

void Calculo_do_fluxo::dimensionamento_tcs ()
{
	//------------------------------------------------------------------------------------------------------------------
	// Dimensionamento dos TCs
	//------------------------------------------------------------------------------------------------------------------

	double I_prim_saturacao, I_primaria_considerada, I_primaria_TC;

	for (i = 0; i < DISJUNTORPROT.size (); i++)
	{
		I_primaria_TC = ( DISJUNTORPROT[i].Icarga );
		I_prim_saturacao = DISJUNTORPROT[i].Icc_max / FS;

		if (I_prim_saturacao > I_primaria_TC)
		{
			I_primaria_considerada = I_prim_saturacao;
			printf ( "O TC do disjuntor %d foi calculado utilizando o criterio da saturacao\n", i );
		}
		else
		{
			I_primaria_considerada = I_primaria_TC;
		}
		if (I_primaria_considerada < 5.0)
		{
			DISJUNTORPROT[i].RTC = 1.0; // 5:5
			DISJUNTORPROT[i].Iprimaria = 5.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 10.0)
		{
			DISJUNTORPROT[i].RTC = 2.0; // 10:5
			DISJUNTORPROT[i].Iprimaria = 10.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 20.0)
		{
			DISJUNTORPROT[i].RTC = 4.0; // 20:5
			DISJUNTORPROT[i].Iprimaria = 20.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 30.0)
		{
			DISJUNTORPROT[i].RTC = 6.0; // 30:5
			DISJUNTORPROT[i].Iprimaria = 30.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 40.0)
		{
			DISJUNTORPROT[i].RTC = 8.0; // 40:5
			DISJUNTORPROT[i].Iprimaria = 4.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 50.0)
		{
			DISJUNTORPROT[i].RTC = 10.0; // 50:5
			DISJUNTORPROT[i].Iprimaria = 50.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 100.0)
		{
			DISJUNTORPROT[i].RTC = 20.0; // 100:5
			DISJUNTORPROT[i].Iprimaria = 100.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 150.0)
		{
			DISJUNTORPROT[i].RTC = 30.0; // 150:5
			DISJUNTORPROT[i].Iprimaria = 150.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 200.0)
		{
			DISJUNTORPROT[i].RTC = 40.0; // 200:5
			DISJUNTORPROT[i].Iprimaria = 200.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 250.0)
		{
			DISJUNTORPROT[i].RTC = 50.0; // 250:5
			DISJUNTORPROT[i].Iprimaria = 250.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 300.0)
		{
			DISJUNTORPROT[i].RTC = 60.0; // 300:5
			DISJUNTORPROT[i].Iprimaria = 300.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 400.0)
		{
			DISJUNTORPROT[i].RTC = 80.0; // 400:5
			DISJUNTORPROT[i].Iprimaria = 400.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 450.0)
		{
			DISJUNTORPROT[i].RTC = 90.0; // 450:5
			DISJUNTORPROT[i].Iprimaria = 450.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 500.0)
		{
			DISJUNTORPROT[i].RTC = 100.0; // 500:5
			DISJUNTORPROT[i].Iprimaria = 500.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 600.0)
		{
			DISJUNTORPROT[i].RTC = 120.0; // 600:5
			DISJUNTORPROT[i].Iprimaria = 600.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 800.0)
		{
			DISJUNTORPROT[i].RTC = 160.0; // 800:5
			DISJUNTORPROT[i].Iprimaria = 800.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 900.0)
		{
			DISJUNTORPROT[i].RTC = 180.0; // 900:5
			DISJUNTORPROT[i].Iprimaria = 900.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 1000.0)
		{
			DISJUNTORPROT[i].RTC = 200.0; // 1000:5
			DISJUNTORPROT[i].Iprimaria = 1000.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else if (I_primaria_considerada < 1200.0)
		{
			DISJUNTORPROT[i].RTC = 240.0; // 1200:5
			DISJUNTORPROT[i].Iprimaria = 1200.0;
			DISJUNTORPROT[i].Isecundaria = 5.0;
		}
		else
		{
			printf ( "Valor de corrente supera o TC\n" );
		}
	}

	for (i = 0; i < CHAVEPROT.size (); i++)
	{
		if (CHAVEPROT[i].TipoCH == 6) // Religador
		{
			I_primaria_TC = ( CHAVEPROT[i].Icarga );
			I_prim_saturacao = CHAVEPROT[i].Icc_max / FS;

			if (I_prim_saturacao > I_primaria_TC)
			{
				I_primaria_considerada = I_prim_saturacao;
				printf ( "O TC do religador %d foi calculado utilizando o criterio da saturacao\n", i );
			}
			else
			{
				I_primaria_considerada = I_primaria_TC;
			}

			if (I_primaria_considerada < 5.0)
			{
				CHAVEPROT[i].RTC = 1.0; // 5:5
				CHAVEPROT[i].Iprimaria = 5.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 10.0)
			{
				CHAVEPROT[i].RTC = 2.0; // 10:5
				CHAVEPROT[i].Iprimaria = 10.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 20.0)
			{
				CHAVEPROT[i].RTC = 4.0; // 20:5
				CHAVEPROT[i].Iprimaria = 20.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 30.0)
			{
				CHAVEPROT[i].RTC = 6.0; // 30:5
				CHAVEPROT[i].Iprimaria = 30.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 40.0)
			{
				CHAVEPROT[i].RTC = 8.0; // 40:5
				CHAVEPROT[i].Iprimaria = 4.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 50.0)
			{
				CHAVEPROT[i].RTC = 10.0; // 50:5
				CHAVEPROT[i].Iprimaria = 50.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 100.0)
			{
				CHAVEPROT[i].RTC = 20.0; // 100:5
				CHAVEPROT[i].Iprimaria = 100.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 150.0)
			{
				CHAVEPROT[i].RTC = 30.0; // 150:5
				CHAVEPROT[i].Iprimaria = 150.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 200.0)
			{
				CHAVEPROT[i].RTC = 40.0; // 200:5
				CHAVEPROT[i].Iprimaria = 200.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 250.0)
			{
				CHAVEPROT[i].RTC = 50.0; // 250:5
				CHAVEPROT[i].Iprimaria = 250.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 300.0)
			{
				CHAVEPROT[i].RTC = 60.0; // 300:5
				CHAVEPROT[i].Iprimaria = 300.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 400.0)
			{
				CHAVEPROT[i].RTC = 80.0; // 400:5
				CHAVEPROT[i].Iprimaria = 400.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 450.0)
			{
				CHAVEPROT[i].RTC = 90.0; // 450:5
				CHAVEPROT[i].Iprimaria = 450.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 500.0)
			{
				CHAVEPROT[i].RTC = 100.0; // 500:5
				CHAVEPROT[i].Iprimaria = 500.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 600.0)
			{
				CHAVEPROT[i].RTC = 120.0; // 600:5
				CHAVEPROT[i].Iprimaria = 600.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 800.0)
			{
				CHAVEPROT[i].RTC = 160.0; // 800:5
				CHAVEPROT[i].Iprimaria = 800.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 900.0)
			{
				CHAVEPROT[i].RTC = 180.0; // 900:5
				CHAVEPROT[i].Iprimaria = 900.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 1000.0)
			{
				CHAVEPROT[i].RTC = 200.0; // 1000:5
				CHAVEPROT[i].Iprimaria = 1000.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else if (I_primaria_considerada < 1200.0)
			{
				CHAVEPROT[i].RTC = 240.0; // 1200:5
				CHAVEPROT[i].Iprimaria = 1200.0;
				CHAVEPROT[i].Isecundaria = 5.0;
			}
			else
			{
				printf ( "Valor de corrente supera o TC\n" );
			}
		}
	}


		//for (j = 0; j < Numero_barras; j++)
		//{
		//	if (DISJUNTORPROT [i].Ramo_ord == j)
		//	{
		//		I_primaria_TC_criterio_1 = I_carga_max [j] / FT; // I_primaria_TC >= k*Icarga/ FT (porém no Icarga deste programa já foi considerado o fator k)
		//		I_primaria_TC_criterio_2 = Icc_3ph     [j] / FS; // I_primaria_TC >= Icc_simetrico / FS
		//		if ( I_primaria_TC_criterio_1 > I_primaria_TC_criterio_2)
		//		{
		//			I_primaria_TC = I_primaria_TC_criterio_1;
		//		}
		//		else
		//		{
		//			I_primaria_TC = I_primaria_TC_criterio_2;
		//		}
		//		if (I_primaria_TC < 10.0)
		//		{
		//			DISJUNTORPROT [i].RTC         = 2.0; // 10:5
		//			DISJUNTORPROT [i].Iprimaria   = 10.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		if (I_primaria_TC < 20.0)
		//		{
		//			DISJUNTORPROT [i].RTC         = 4.0; // 20:5
		//			DISJUNTORPROT [i].Iprimaria   = 20.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		if (I_primaria_TC < 30.0)
		//		{
		//			DISJUNTORPROT [i].RTC         = 6.0; // 30:5
		//			DISJUNTORPROT [i].Iprimaria   = 30.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		if (I_primaria_TC < 40.0)
		//		{
		//			DISJUNTORPROT [i].RTC         = 8.0; // 40:5
		//			DISJUNTORPROT [i].Iprimaria   = 4.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		if (I_primaria_TC < 50.0)
		//		{
		//			DISJUNTORPROT [i].RTC         = 10.0; // 50:5
		//			DISJUNTORPROT [i].Iprimaria   = 50.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		else if (I_primaria_TC < 100.0)
		//		{
		//			DISJUNTORPROT [i].RTC = 20.0; // 100:5
		//			DISJUNTORPROT [i].Iprimaria   = 100.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		else if (I_primaria_TC < 150.0)
		//		{
		//			DISJUNTORPROT [i].RTC = 30.0; // 150:5
		//			DISJUNTORPROT [i].Iprimaria   = 150.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		else if (I_primaria_TC < 200.0)
		//		{
		//			DISJUNTORPROT [i].RTC = 40.0; // 200:5
		//			DISJUNTORPROT [i].Iprimaria   = 200.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		else if (I_primaria_TC < 250.0)
		//		{
		//			DISJUNTORPROT [i].RTC = 50.0; // 250:5
		//			DISJUNTORPROT [i].Iprimaria   = 250.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		else if (I_primaria_TC < 300.0)
		//		{
		//			DISJUNTORPROT [i].RTC = 60.0; // 300:5
		//			DISJUNTORPROT [i].Iprimaria   = 300.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		else if (I_primaria_TC < 400.0)
		//		{
		//			DISJUNTORPROT [i].RTC = 80.0; // 400:5
		//			DISJUNTORPROT [i].Iprimaria   = 400.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		else if (I_primaria_TC < 450.0)
		//		{
		//			DISJUNTORPROT [i].RTC = 90.0; // 450:5
		//			DISJUNTORPROT [i].Iprimaria   = 450.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		else if (I_primaria_TC < 500.0)
		//		{
		//			DISJUNTORPROT [i].RTC = 100.0; // 500:5
		//			DISJUNTORPROT [i].Iprimaria   = 500.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		else if (I_primaria_TC < 600.0)
		//		{
		//			DISJUNTORPROT [i].RTC = 120.0; // 600:5
		//			DISJUNTORPROT [i].Iprimaria   = 600.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		else if (I_primaria_TC < 800.0)
		//		{
		//			DISJUNTORPROT [i].RTC = 160.0; // 800:5
		//			DISJUNTORPROT [i].Iprimaria   = 800.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		else if (I_primaria_TC < 900.0)
		//		{
		//			DISJUNTORPROT [i].RTC = 180.0; // 900:5
		//			DISJUNTORPROT [i].Iprimaria   = 900.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		else if (I_primaria_TC < 1000.0)
		//		{
		//			DISJUNTORPROT [i].RTC = 200.0; // 1000:5
		//			DISJUNTORPROT [i].Iprimaria   = 1000.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		else if (I_primaria_TC < 1200.0)
		//		{
		//			DISJUNTORPROT [i].RTC = 240.0; // 1200:5
		//			DISJUNTORPROT [i].Iprimaria   = 1200.0;
		//			DISJUNTORPROT [i].Isecundaria = 5.0;
		//		}
		//		else 
		//		{
		//			printf ("Valor de corrente supera o TC\n");
		//		}
		//		break;
		//	}
		//}
}

float Calculo_do_fluxo::Dial_rele(int Tipo_Norma, int Tipo_Curva, float M_rele, float T_procurado)
{
	if (Tipo_Norma == 1) // IEC/ABNT
	{
		if (Tipo_Curva == 1)
		{
			a_rele = 0.14;
			n_rele = 0.02;
			Tipo_curva_string = "Inversa";
		}
		else if ( Tipo_Curva == 2)
		{
			a_rele = 13.5;
			n_rele = 1.0;
			Tipo_curva_string = "Muito Inversa";
		}
		else if (Tipo_Curva == 3)
		{
			a_rele = 80;
			n_rele = 2.0;
			Tipo_curva_string = "Extremamente Inversa";
		}
		else if (Tipo_Curva == 4)
		{
			a_rele = 0.050;
			n_rele = 0.04;
			Tipo_curva_string = "Pouco Inversa";
		}
		else
		{
			printf ("Disp erro tipo de curva \n");
		}

		Dial_Rele =  T_procurado / ( a_rele / ( pow (M_rele, n_rele) - 1) );

	}
	else if (Tipo_Norma == 2) // IAC (GE)
	{
		if (Tipo_Curva == 1)
		{
			a_rele =  0.2078;
			b_rele =  0.8630;
			c_rele =  0.8;
			d_rele = -0.4180;
			e_rele =  0.1947;
			Tipo_curva_string = "Inversa";
		}
		else if (Tipo_Curva == 2)
		{
			a_rele = 0.09;
			b_rele = 0.7955;
			c_rele = 0.1;
			d_rele = -1.2885;
			e_rele = 7.9586;
			Tipo_curva_string = "Muito Inversa";
		}
		else if (Tipo_Curva == 3)
		{
			a_rele = 0.004;
			b_rele = 0.6379;
			c_rele = 0.62;
			d_rele = 1.7872;
			e_rele = 0.2461;
			Tipo_curva_string = "Extremamente Inversa";
		}
		else if (Tipo_Curva == 4)
		{
			a_rele = 0.0428;
			b_rele = 0.0609;
			c_rele = 0.62;
			d_rele =-0.001;
			e_rele = 0.0221;
			Tipo_curva_string = "Pouco Inversa";
		}
		else
		{
			printf ("Disp erro tipo de curva \n");
		}

		Dial_Rele = T_procurado / ( a_rele + b_rele / (M_rele - c_rele) + d_rele / pow ( (M_rele - c_rele), 2.0) + e_rele / pow ( (M_rele - c_rele), 3.0) );

	}
	else if (Tipo_Norma == 3) // US
	{
		if (Tipo_Curva == 1)
		{
			a_rele = 0.18;
			b_rele = 5.95;
			p_rele = 2.0;
			Tipo_curva_string = "Inversa";
		}
		else if (Tipo_Curva == 2)
		{
			a_rele = 0.0963;
			b_rele = 3.88;
			p_rele = 2.0;
			Tipo_curva_string = "Muito Inversa";
		}
		else if (Tipo_Curva == 3)
		{
			a_rele = 0.0352;
			b_rele = 5.67;
			p_rele = 2.0;
			Tipo_curva_string = "Extremamente Inversa";
		}
		else if (Tipo_Curva == 4)
		{
			a_rele = 0.00262;
			b_rele = 0.00342;
			p_rele = 0.02;
			Tipo_curva_string = "Pouco Inversa";
		}
		else if (Tipo_Curva == 5)
		{
			a_rele = 0.0226;
			b_rele = 0.0104;
			p_rele = 0.02;
			Tipo_curva_string = "Moderadamente Inversa";
		}
		else
		{
			printf ("Disp erro tipo de curva \n");
		}

		Dial_Rele = T_procurado / (a_rele + b_rele / (pow ( M_rele, p_rele) - 1) );

	}
	else if (Tipo_Norma == 4) // ANSI/IEEE
	{
		if (Tipo_Curva == 1)
		{
			a_rele = 19.61;
			b_rele = 0.491;
			p_rele = 2;
			Tipo_curva_string = "Muito Inversa";
		}
		else if (Tipo_Curva == 2)
		{
			a_rele = 28.2;
			b_rele = 0.1217;
			p_rele = 2;
			Tipo_curva_string = "Extremamente Inversa";
		}
		else if (Tipo_Curva == 3)
		{
			a_rele = 0.0515;
			b_rele = 0.114;
			p_rele = 0.02;
			Tipo_curva_string = "Moderamente Inversa";
		}
		else
		{
			printf ("Disp erro tipo de curva \n");
		}

		Dial_Rele = T_procurado / (b_rele + a_rele / (pow ( M_rele, p_rele) - 1) );

	}
	return Dial_Rele;
}

float Calculo_do_fluxo::T_rele (int Tipo_Norma, int Tipo_Curva, float M_rele, float Dial)
{	
	if (Tipo_Norma == 1) // IEC/ABNT
	{
		if (Tipo_Curva == 1)
		{
			a_rele = 0.14;
			n_rele = 0.02;
			Tipo_curva_string = "Inversa";
		}
		else if ( Tipo_Curva == 2)
		{
			a_rele = 13.5;
			n_rele = 1.0;
			Tipo_curva_string = "Muito Inversa";
		}
		else if (Tipo_Curva == 3)
		{
			a_rele = 80;
			n_rele = 2.0;
			Tipo_curva_string = "Extremamente Inversa";
		}
		else if (Tipo_Curva == 4)
		{
			a_rele = 120.0;
			n_rele = 1.0;
			Tipo_curva_string = "Pouco Inversa";
		}
		else
		{
			printf ("Disp erro tipo de curva \n");
		}

		Tempo_rele = a_rele * Dial / (pow (M_rele, n_rele) - 1);

	}
	else if (Tipo_Norma == 2) // IAC (GE)
	{
		if (Tipo_Curva == 1)
		{
			a_rele =  0.2078;
			b_rele =  0.8630;
			c_rele =  0.8;
			d_rele = -0.4180;
			e_rele =  0.1947;
			Tipo_curva_string = "Inversa";
		}
		else if (Tipo_Curva == 2)
		{
			a_rele = 0.09;
			b_rele = 0.7955;
			c_rele = 0.1;
			d_rele = -1.2885;
			e_rele = 7.9586;
			Tipo_curva_string = "Muito Inversa";
		}
		else if (Tipo_Curva == 3)
		{
			a_rele = 0.004;
			b_rele = 0.6379;
			c_rele = 0.62;
			d_rele = 1.7872;
			e_rele = 0.2461;
			Tipo_curva_string = "Extremamente Inversa";
		}
		else if (Tipo_Curva == 4)
		{
			a_rele = 0.0428;
			b_rele = 0.0609;
			c_rele = 0.62;
			d_rele =-0.001;
			e_rele = 0.0221;
			Tipo_curva_string = "Pouco Inversa";
		}
		else
		{
			printf ("Disp erro tipo de curva \n");
		}

		Tempo_rele = Dial * (a_rele + b_rele / (M_rele - c_rele) + d_rele / pow ( (M_rele - c_rele), 2.0) + e_rele / pow ( (M_rele - c_rele), 3.0) );

	}
	else if (Tipo_Norma == 3) // US
	{
		if (Tipo_Curva == 1)
		{
			a_rele = 0.18;
			b_rele = 5.95;
			p_rele = 2.0;
			Tipo_curva_string = "Inversa";
		}
		else if (Tipo_Curva == 2)
		{
			a_rele = 0.0963;
			b_rele = 3.88;
			p_rele = 2.0;
			Tipo_curva_string = "Muito Inversa";
		}
		else if (Tipo_Curva == 3)
		{
			a_rele = 0.0352;
			b_rele = 5.67;
			p_rele = 2.0;
			Tipo_curva_string = "Extremamente Inversa";
		}
		else if (Tipo_Curva == 4)
		{
			a_rele = 0.00262;
			b_rele = 0.00342;
			p_rele = 0.02;
			Tipo_curva_string = "Pouco Inversa";
		}
		else if (Tipo_Curva == 5)
		{
			a_rele = 0.0226;
			b_rele = 0.0104;
			p_rele = 0.02;
			Tipo_curva_string = "Moderadamente Inversa";
		}
		else
		{
			printf ("Disp erro tipo de curva \n");
		}

		Tempo_rele = Dial * (a_rele + b_rele / (pow ( M_rele, p_rele) - 1) );

	}
	else if (Tipo_Norma == 4) // ANSI/IEEE
	{
		if (Tipo_Curva == 1)
		{
			a_rele = 19.61;
			b_rele = 0.491;
			p_rele = 2;
			Tipo_curva_string = "Muito Inversa";
		}
		else if (Tipo_Curva == 2)
		{
			a_rele = 28.2;
			b_rele = 0.1217;
			p_rele = 2;
			Tipo_curva_string = "Extremamente Inversa";
		}
		else if (Tipo_Curva == 3)
		{
			a_rele = 0.0515;
			b_rele = 0.114;
			p_rele = 0.02;
			Tipo_curva_string = "Moderamente Inversa";
		}
		else
		{
			printf ("Disp erro tipo de curva \n");
		}

		Tempo_rele = Dial * (b_rele + a_rele / (pow ( M_rele, p_rele) - 1) );

	}
	return Tempo_rele;
}

void Calculo_do_fluxo::coordenação_reles ()
{
	//------------------------------------------------------------------------------------------------------------------
    // Declaração de variáveis
    //------------------------------------------------------------------------------------------------------------------

	int   Ramo_protecao_primaria;
	int   Ramo_menor_icc_prot_primaria;
	int   aux_maior_fusivel;
	float aux_IccMax;
	float aux_IccMax_neutro;
	int   aux_verifica_filhos_DJ, aux_verifica_filhos_religadores;
	int   seletivo;    // caso essa variável seja igual a 1, o processo para porque já é seletivo
	int   seletivo_neutro;    // caso essa variável seja igual a 1, o processo para porque já é seletivo
	int   aux_pos_menor_delta_T;
	int   aux_pos_menor_delta_T_neutro;
	float aux_delta_Icc;
	float aux_delta_Icc_neutro;
	float m_rele_aux;
	float m_rele_aux_neutro;
	float aux_menor_delta_T;
	float aux_menor_delta_T_neutro;
	float aux_T_procurado;
	float aux_T_procurado_neutro;
	float aux_Dial;
	float aux_Dial_neutro;
	float aux_Ipickup_fase;
	float aux_Ipickup_neutro;
	float Menor_Delta_T_protecao_retaguarda_primaria;
	float Menor_Delta_T_protecao_retaguarda_primaria_neutro;
	float m_rele_aux_primaria;
	float m_rele_aux_primaria_neutro;
	float Intervalo_Coord;
	float Intervalo_Coord_neutro;
	double Tap_crit_1;        // Tape_temporizado_fase >= (K * Icarga)/ RTC
	double Tap_crit_1_neutro; // Tape_temporizado_fase >= (K * Icarga)/ RTC
	double Ipickup_crit_1;
	double Ipickup_crit_1_neutro; 
	double Tap_crit_2;        // Tape_temporizado_fase < Icc_2ph_min_protegido / (F_seguranca*FI*RTC)
	double Ipickup_crit_2;
	double Tap_crit_aux;
	double Ipickup_crit_aux;
	float M_rele [100] [100]; // Máximo de 100 relés em série
	float K_rele [100] [100];

	Icc_analisados                               = new float [aux_intervalo + 1];
	TDS_analisados                               = new float [aux_intervalo + 1];
	T_protecao_retaguarda                        = new float [aux_intervalo + 1];
	T_protecao_primaria                          = new float [aux_intervalo + 1];
	Delta_T_protecao_retaguarda_primaria         = new float [aux_intervalo + 1];
	T_fusivel                                    = new float [aux_intervalo + 1];

	Icc_analisados_neutro                        = new float [aux_intervalo + 1];
	TDS_analisados_neutro                        = new float [aux_intervalo + 1];
	T_protecao_retaguarda_neutro                 = new float [aux_intervalo + 1];
	T_protecao_primaria_neutro                   = new float [aux_intervalo + 1];
	Delta_T_protecao_retaguarda_primaria_neutro  = new float [aux_intervalo + 1];
	T_fusivel_neutro                             = new float [aux_intervalo + 1];
	tipo_curva  = 2; // 1 = Inversa; 2 = Muito inversa; 3 = Extremamente inversa; 4 = Pouco inversa
	norma_curva = 1; // 1 - IEC/ABNT 2 - IAC (GE) - 3 US - 4 -ANSI/IEEE

	//------------------------------------------------------------------------------------------------------------------
    // Ajuste das correntes de pick-up do relé de fase e neutro (51) - Temporizado
    //------------------------------------------------------------------------------------------------------------------
	
	for ( i = 0; i < DISJUNTORPROT.size (); i++)
	{
		Tap_crit_1            = (DISJUNTORPROT [i].Icarga / DISJUNTORPROT [i].RTC);      
		Tap_crit_1_neutro     = K_desequilibrio * DISJUNTORPROT [i].Icarga / DISJUNTORPROT [i].RTC;
		Ipickup_crit_1        = (DISJUNTORPROT [i].Icarga); 
		Ipickup_crit_1_neutro = K_desequilibrio * DISJUNTORPROT [i].Icarga;

		DISJUNTORPROT [i].Ipickup_fase           = (Ipickup_crit_1);
		DISJUNTORPROT [i].Ipickup_neutro         = (Ipickup_crit_1_neutro);
		DISJUNTORPROT [i].Tap_Temporizado_fase   = (Tap_crit_1);
		DISJUNTORPROT [i].Tap_Temporizado_neutro = (Tap_crit_1_neutro);
	}

	for ( i = 0; i < CHAVEPROT.size (); i++)
	{
		if ( CHAVEPROT[i].TipoCH == 6 )
		{
			Ipickup_crit_1        =  (CHAVEPROT [i].Icarga);
			Ipickup_crit_1_neutro = K_desequilibrio * CHAVEPROT [i].Icarga;

			CHAVEPROT [i].Religador_Ipickup_fase   = (Ipickup_crit_1       );
			CHAVEPROT [i].Religador_Ipickup_neutro = (Ipickup_crit_1_neutro);
		}
	}
	
	//------------------------------------------------------------------------------------------------------------------
    // Inicia os Dial dos religadores e fusíveis com valor de dial mínimo
    //------------------------------------------------------------------------------------------------------------------

	for ( i = 0; i < DISJUNTORPROT.size(); i++ )
	{
		DISJUNTORPROT [i].Dial_fase            = Dial_min;
		DISJUNTORPROT [i].Dial_neutro          = Dial_min;
		DISJUNTORPROT [i].Icc_1f_min_protegido = 999999.99; // Valor grande inicial
		DISJUNTORPROT [i].Icc_2f_min_protegido = 999999.99;

		for ( j = 0; j < DISJUNTORPROT [i].STRUCTFILHOSDJ.size (); j++)
		{
			if ( DISJUNTORPROT [i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "CH")
			{
				DISJUNTORPROT [i].STRUCTFILHOSDJ[j].Pos_struct_Filho = IndexStructCH [DISJUNTORPROT [i].STRUCTFILHOSDJ[j].Ramos_ord_FilhoDJ];
			}
			else if ( DISJUNTORPROT [i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "TR")
			{
				DISJUNTORPROT [i].STRUCTFILHOSDJ[j].Pos_struct_Filho = IndexStruct   [DISJUNTORPROT [i].STRUCTFILHOSDJ[j].Ramos_ord_FilhoDJ];
			}
			else if ( DISJUNTORPROT [i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "DJ")
			{
				DISJUNTORPROT [i].STRUCTFILHOSDJ[j].Pos_struct_Filho = IndexStructDJ [DISJUNTORPROT [i].STRUCTFILHOSDJ[j].Ramos_ord_FilhoDJ];
			}
		}
	}

	for ( i = 0; i < CHAVEPROT.size(); i++ )
	{
		if ( CHAVEPROT [i].TipoCH == 6 )
		{
			CHAVEPROT [i].Religador_Dial_fase_rapida      = Dial_min;
			CHAVEPROT [i].Religador_Dial_fase_retardada   = Dial_min;
			CHAVEPROT [i].Religador_Dial_neutro_rapida    = Dial_min;
			CHAVEPROT [i].Religador_Dial_neutro_retardada = Dial_min;
			CHAVEPROT [i].Abertura_Rapida_Coordenada      = "Sim";
			CHAVEPROT [i].Icc_1f_min_protegido            = 999999.99; // Valor grande inicial
			CHAVEPROT [i].Icc_2f_min_protegido            = 999999.99;
			//CHAVEPROT [i].T_atuacao_inst                  = 999999.99;
			//CHAVEPROT [i].T_atuacao_inst_neutro           = 999999.99;
		}

		if ( CHAVEPROT [i].TipoCH == 0 )
		{
			CHAVEPROT [i].Icc_1f_min_protegido = 999999.99; // Valor grande inicial
			CHAVEPROT [i].Icc_2f_min_protegido = 999999.99;
		}

		for ( j = 0; j < CHAVEPROT [i].STRUCTFILHOSCH.size (); j++)
		{
			if ( CHAVEPROT [i].STRUCTFILHOSCH [j].TiposFilhosCH == "CH")
			{
				CHAVEPROT [i].STRUCTFILHOSCH [j].Pos_struct_Filho = IndexStructCH [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH];
			}
			else if ( CHAVEPROT [i].STRUCTFILHOSCH [j].TiposFilhosCH == "TR")
			{
				CHAVEPROT [i].STRUCTFILHOSCH [j].Pos_struct_Filho = IndexStruct   [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH];
			}
			else if ( CHAVEPROT [i].STRUCTFILHOSCH [j].TiposFilhosCH == "DJ")
			{
				CHAVEPROT [i].STRUCTFILHOSCH [j].Pos_struct_Filho = IndexStructDJ [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH];
			}
		}
	}

	//------------------------------------------------------------------------------------------------------------------
    // Rotina para descobrir o nível de CC mínimo em cada chave fusível
    //------------------------------------------------------------------------------------------------------------------
	// A rotina abaixo funciona da seguinte maneira: É encontrado o menor nível de curto-circuito (1f ou 2f) para cada chave fusível.

	for ( i =  CHAVEPROT.size () - 1 ; i > - 1; i -- ) // Primeiro será coordenado com o maior fusível (se houver) depois, coordena com o religador
	{
		if ( CHAVEPROT [i].TipoCH == 0 ) // Verifica se o dispositivo de retaguarda (protegido) é um chave fusivel
		{
			if (CHAVEPROT [i].STRUCTFILHOSCH.size () == 0)
			{
				CHAVEPROT [i].Icc_2f_min_protegido = CHAVEPROT [i].Icc2f_min;
				CHAVEPROT [i].Icc_1f_min_protegido = CHAVEPROT [i].Icc1f_min;
			}

			for ( k = 0; k < CHAVEPROT [i].STRUCTFILHOSCH.size (); k++)
			{
				Ramo_protecao_primaria = CHAVEPROT [i].STRUCTFILHOSCH [k].Ramos_ord_FilhoCH;

				if ( CHAVEPROT [i].STRUCTFILHOSCH[k].TiposFilhosCH == "CH" ) // Caso o dispositivo protetor seja uma chave
				{					
					aux_Icc_min        = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc2f_min; // Valores em [A]
					aux_Icc_min_neutro = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f_min; // Valores em [A]
				}
				else if ( CHAVEPROT [i].STRUCTFILHOSCH[k].TiposFilhosCH == "DJ" ) // Caso o dispositivo protetor seja um DJ
				{					
					aux_Icc_min        = DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Icc2f_min; // Valores em [A]
					aux_Icc_min_neutro = DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Icc1f_min; // Valores em [A]
				}
				else if ( CHAVEPROT [i].STRUCTFILHOSCH[k].TiposFilhosCH == "TR" ) // Caso o dispositivo protetor seja uma chave
				{	
					aux_Icc_min        = TRAFOS_DISTRI [IndexStruct [Ramo_protecao_primaria]].Icc2f_min;
					aux_Icc_min_neutro = TRAFOS_DISTRI [IndexStruct [Ramo_protecao_primaria]].Icc1f_min;
				}			

				if ( aux_Icc_min < CHAVEPROT [i].Icc_2f_min_protegido ) // Atualiza a struct que encontra o menor valor de CC que o dispositivo deve atuar
				{
					CHAVEPROT [i].Icc_2f_min_protegido = aux_Icc_min;
				}

				if ( aux_Icc_min_neutro < CHAVEPROT [i].Icc_1f_min_protegido ) // Atualiza a struct que encontra o menor valor de CC que o dispositivo deve atuar
				{
					CHAVEPROT [i].Icc_1f_min_protegido = aux_Icc_min_neutro;
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------------------------
    // Rotina para descobir o nível mínimo de curto-circuito bifásico e monofásico dos disjuntores
    //------------------------------------------------------------------------------------------------------------------
	int aux_struct_DJ;
	int aux_struct_CH;

	for (i = DISJUNTORPROT.size() - 1; i > - 1; i--)
	{
		for (j = 0; j < DISJUNTORPROT[i].STRUCTFILHOSDJ.size(); j++)
		{
			if (DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "CH")
			{
				if (DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TipoChave == 0) // Caso seja um elo
				{
					if (CHAVEPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc_2f_min_protegido < DISJUNTORPROT[i].Icc_2f_min_protegido)
					{
						DISJUNTORPROT[i].Icc_2f_min_protegido = CHAVEPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc_2f_min_protegido;
						printf("DJ %d Icc_2ph = %f CH = %d \n", i, DISJUNTORPROT[i].Icc_2f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho);
					}
					if (CHAVEPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc_1f_min_protegido < DISJUNTORPROT[i].Icc_1f_min_protegido)
					{
						DISJUNTORPROT[i].Icc_1f_min_protegido = CHAVEPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc_1f_min_protegido;
						printf("DJ %d Icc_1ph = %f CH = %d \n", i, DISJUNTORPROT[i].Icc_1f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho);
					}
				}
				else if (DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TipoChave == 6) // Caso seja um religador
				{
					if (CHAVEPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].STRUCTFILHOSCH.size() == 0)
					{
						if (CHAVEPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc2f_min < DISJUNTORPROT[i].Icc_2f_min_protegido)
						{
							DISJUNTORPROT[i].Icc_2f_min_protegido = CHAVEPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc2f_min;
							printf("DJ %d Icc_2ph = %f CH = %d \n", i, DISJUNTORPROT[i].Icc_2f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho);
						}
						if (CHAVEPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc1f_min < DISJUNTORPROT[i].Icc_1f_min_protegido)
						{
							DISJUNTORPROT[i].Icc_1f_min_protegido = CHAVEPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc1f_min;
							printf("DJ %d Icc_1ph = %f CH = %d \n", i, DISJUNTORPROT[i].Icc_1f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho);
						}
					}
					else
					{
						{
							aux_struct_CH = DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho;
							for (k = 0; k < CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH.size(); k++)
							{
								if (CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].TiposFilhosCH == "CH")
								{
									if (CHAVEPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc2f_min < DISJUNTORPROT[i].Icc_2f_min_protegido)
									{
										DISJUNTORPROT[i].Icc_2f_min_protegido = CHAVEPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc2f_min;
										printf("DJ %d Icc_2ph = %f CH = %d, CH filho = %d \n", i, DISJUNTORPROT[i].Icc_2f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho, CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho);
									}
									if (CHAVEPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc1f_min < DISJUNTORPROT[i].Icc_1f_min_protegido)
									{
										DISJUNTORPROT[i].Icc_1f_min_protegido = CHAVEPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc1f_min;
										printf("DJ %d Icc_1ph = %f CH = %d, CH filho = %d \n", i, DISJUNTORPROT[i].Icc_1f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho, CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho);
									}
								}
								else if (CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].TiposFilhosCH == "TR")
								{
									if (TRAFOS_DISTRI[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc2f_min < DISJUNTORPROT[i].Icc_2f_min_protegido)
									{
										DISJUNTORPROT[i].Icc_2f_min_protegido = TRAFOS_DISTRI[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc2f_min;
										printf("DJ %d Icc_2ph = %f CH = %d, TR filho = %d \n", i, DISJUNTORPROT[i].Icc_2f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho, CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho);
									}
									if (TRAFOS_DISTRI[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc1f_min < DISJUNTORPROT[i].Icc_1f_min_protegido)
									{
										DISJUNTORPROT[i].Icc_1f_min_protegido = TRAFOS_DISTRI[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc1f_min;
										printf("DJ %d Icc_1ph = %f CH = %d, TR filho = %d \n", i, DISJUNTORPROT[i].Icc_1f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho, CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho);
									}
								}
								else if (CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].TiposFilhosCH == "DJ")
								{
									if (DISJUNTORPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc2f_min < DISJUNTORPROT[i].Icc_2f_min_protegido)
									{
										DISJUNTORPROT[i].Icc_2f_min_protegido = DISJUNTORPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc2f_min;
										printf("DJ %d Icc_2ph = %f CH = %d, DJ filho = %d \n", i, DISJUNTORPROT[i].Icc_2f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho, CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho);
									}
									if (DISJUNTORPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc1f_min < DISJUNTORPROT[i].Icc_1f_min_protegido)
									{
										DISJUNTORPROT[i].Icc_1f_min_protegido = DISJUNTORPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc1f_min;
										printf("DJ %d Icc_1ph = %f CH = %d, DJ filho = %d \n", i, DISJUNTORPROT[i].Icc_1f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho, CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho);
									}
								}
							}
						}
					}
				}
			}
			else if (DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "TR")
			{
				if (TRAFOS_DISTRI[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc2f_min < DISJUNTORPROT[i].Icc_2f_min_protegido)
				{
					DISJUNTORPROT[i].Icc_2f_min_protegido = TRAFOS_DISTRI[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc2f_min;
					printf("DJ %d Icc_2ph = %f TR = %d \n", i, DISJUNTORPROT[i].Icc_2f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho);
				}
				if (TRAFOS_DISTRI[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc1f_min < DISJUNTORPROT[i].Icc_1f_min_protegido)
				{
					DISJUNTORPROT[i].Icc_1f_min_protegido = TRAFOS_DISTRI[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc1f_min;
					printf("DJ %d Icc_1ph = %f TR = %d \n", i, DISJUNTORPROT[i].Icc_1f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho);
				}
			}
			else if (DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "DJ")
			{
				if (DISJUNTORPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].STRUCTFILHOSDJ.size() == 0)
					{
						if (DISJUNTORPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc2f_min < DISJUNTORPROT[i].Icc_2f_min_protegido)
						{
							DISJUNTORPROT[i].Icc_2f_min_protegido = DISJUNTORPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc2f_min;
							printf("DJ %d Icc_2ph = %f DJ = %d \n", i, DISJUNTORPROT[i].Icc_2f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho);
						}
						if (DISJUNTORPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc1f_min < DISJUNTORPROT[i].Icc_1f_min_protegido)
						{
							DISJUNTORPROT[i].Icc_1f_min_protegido = DISJUNTORPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc1f_min;
							printf("DJ %d Icc_1ph = %f DJ = %d \n", i, DISJUNTORPROT[i].Icc_1f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho);
						}
					}
					else
					{
						{
							aux_struct_CH = DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho;
							for (k = 0; k < DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ.size(); k++)
							{
								if (DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].TiposFilhosDJ == "CH")
								{
									
									if (CHAVEPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc2f_min < DISJUNTORPROT[i].Icc_2f_min_protegido)
									{
										
										DISJUNTORPROT[i].Icc_2f_min_protegido = CHAVEPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc2f_min;
										printf("DJ %d Icc_2ph = %f DJ = %d, CH filho = %d \n", i, DISJUNTORPROT[i].Icc_2f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho, DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho);
									}
									if (CHAVEPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc1f_min < DISJUNTORPROT[i].Icc_1f_min_protegido)
									{
										DISJUNTORPROT[i].Icc_1f_min_protegido = CHAVEPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc1f_min;
										printf("DJ %d Icc_1ph = %f DJ = %d, CH filho = %d \n", i, DISJUNTORPROT[i].Icc_1f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho, DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho);
									}
								}
								else if (DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].TiposFilhosDJ == "TR")
								{
									if (TRAFOS_DISTRI[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc2f_min < DISJUNTORPROT[i].Icc_2f_min_protegido)
									{
										DISJUNTORPROT[i].Icc_2f_min_protegido = TRAFOS_DISTRI[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc2f_min;
										printf("DJ %d Icc_2ph = %f DJ = %d, TR filho = %d \n", i, DISJUNTORPROT[i].Icc_2f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho, DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho);
									}
									if (TRAFOS_DISTRI[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc1f_min < DISJUNTORPROT[i].Icc_1f_min_protegido)
									{
										DISJUNTORPROT[i].Icc_1f_min_protegido = TRAFOS_DISTRI[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc1f_min;
										printf("DJ %d Icc_1ph = %f DJ = %d, TR filho = %d \n", i, DISJUNTORPROT[i].Icc_1f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho, DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho);
									}
								}
								else if (DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].TiposFilhosDJ == "DJ")
								{
									if (DISJUNTORPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc2f_min < DISJUNTORPROT[i].Icc_2f_min_protegido)
									{
										DISJUNTORPROT[i].Icc_2f_min_protegido = DISJUNTORPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc2f_min;
										printf("DJ %d Icc_2ph = %f DJ = %d, DJ filho = %d \n", i, DISJUNTORPROT[i].Icc_2f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho, DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho);
									}
									if (DISJUNTORPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc1f_min < DISJUNTORPROT[i].Icc_1f_min_protegido)
									{
										DISJUNTORPROT[i].Icc_1f_min_protegido = DISJUNTORPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc1f_min;
										printf("DJ %d Icc_1ph = %f DJ = %d, DJ filho = %d \n", i, DISJUNTORPROT[i].Icc_1f_min_protegido, DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho, DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho);
									}
								}
							}
						}
					}
				}
			}
		
	}

	for (i = CHAVEPROT.size() - 1; i > - 1; i--)
	{
		if (CHAVEPROT[i].TipoCH == 6) // caso seja um religador
		{
			for (j = 0; j < CHAVEPROT[i].STRUCTFILHOSCH.size(); j++)
			{
				if (CHAVEPROT[i].STRUCTFILHOSCH[j].TiposFilhosCH == "CH")
				{
					if (CHAVEPROT[i].STRUCTFILHOSCH[j].TipoChave == 0) // Caso seja um elo
					{
						if (CHAVEPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc_2f_min_protegido < CHAVEPROT[i].Icc_2f_min_protegido)
						{
							CHAVEPROT[i].Icc_2f_min_protegido = CHAVEPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc_2f_min_protegido;
							printf("CH %d Icc_2ph = %f CH = %d \n", i, CHAVEPROT[i].Icc_2f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho);
						}
						if (CHAVEPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc_1f_min_protegido < CHAVEPROT[i].Icc_1f_min_protegido)
						{
							CHAVEPROT[i].Icc_1f_min_protegido = CHAVEPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc_1f_min_protegido;
							printf("CH %d Icc_1ph = %f CH = %d \n", i, CHAVEPROT[i].Icc_1f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho);
						}
					}
					else if (CHAVEPROT[i].STRUCTFILHOSCH[j].TipoChave == 6) // Caso seja um religador
					{
						if (CHAVEPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].STRUCTFILHOSCH.size() == 0)
						{
							if (CHAVEPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc2f_min < CHAVEPROT[i].Icc_2f_min_protegido)
							{
								CHAVEPROT[i].Icc_2f_min_protegido = CHAVEPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc2f_min;
								printf("CH %d Icc_2ph = %f CH = %d \n", i, CHAVEPROT[i].Icc_2f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho);
							}
							if (CHAVEPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc1f_min < CHAVEPROT[i].Icc_1f_min_protegido)
							{
								CHAVEPROT[i].Icc_1f_min_protegido = CHAVEPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc1f_min;
								printf("CH %d Icc_1ph = %f CH = %d \n", i, CHAVEPROT[i].Icc_1f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho);
							}
						}
						else
						{
							{
								aux_struct_CH = CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho;
								for (k = 0; k < CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH.size(); k++)
								{
									if (CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].TiposFilhosCH == "CH")
									{
										if (CHAVEPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc2f_min < CHAVEPROT[i].Icc_2f_min_protegido)
										{
											CHAVEPROT[i].Icc_2f_min_protegido = CHAVEPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc2f_min;
											printf("CH %d Icc_2ph = %f CH = %d, CH filho = %d \n", i, CHAVEPROT[i].Icc_2f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho, CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho);
										}
										if (CHAVEPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc1f_min < CHAVEPROT[i].Icc_1f_min_protegido)
										{
											CHAVEPROT[i].Icc_1f_min_protegido = CHAVEPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc1f_min;
											printf("CH %d Icc_1ph = %f CH = %d, CH filho = %d \n", i, CHAVEPROT[i].Icc_1f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho, CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho);
										}
									}
									else if (CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].TiposFilhosCH == "TR")
									{
										if (TRAFOS_DISTRI[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc2f_min < CHAVEPROT[i].Icc_2f_min_protegido)
										{
											CHAVEPROT[i].Icc_2f_min_protegido = TRAFOS_DISTRI[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc2f_min;
											printf("CH %d Icc_2ph = %f CH = %d, TR filho = %d \n", i, CHAVEPROT[i].Icc_2f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho, CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho);
										}
										if (TRAFOS_DISTRI[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc1f_min < CHAVEPROT[i].Icc_1f_min_protegido)
										{
											CHAVEPROT[i].Icc_1f_min_protegido = TRAFOS_DISTRI[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc1f_min;
											printf("CH %d Icc_1ph = %f CH = %d, TR filho = %d \n", i, CHAVEPROT[i].Icc_1f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho, CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho);
										}
									}
									else if (CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].TiposFilhosCH == "DJ")
									{
										if (DISJUNTORPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc2f_min < CHAVEPROT[i].Icc_2f_min_protegido)
										{
											CHAVEPROT[i].Icc_2f_min_protegido = DISJUNTORPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc2f_min;
											printf("CH %d Icc_2ph = %f CH = %d, DJ filho = %d \n", i, CHAVEPROT[i].Icc_2f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho, CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho);
										}
										if (DISJUNTORPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc1f_min < CHAVEPROT[i].Icc_1f_min_protegido)
										{
											CHAVEPROT[i].Icc_1f_min_protegido = DISJUNTORPROT[CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho].Icc1f_min;
											printf("CH %d Icc_1ph = %f CH = %d, DJ filho = %d \n", i, CHAVEPROT[i].Icc_1f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho, CHAVEPROT[aux_struct_CH].STRUCTFILHOSCH[k].Pos_struct_Filho);
										}
									}
								}
							}
						}
					}
				}
				else if (CHAVEPROT[i].STRUCTFILHOSCH[j].TiposFilhosCH == "TR")
				{
					if (TRAFOS_DISTRI[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc2f_min < CHAVEPROT[i].Icc_2f_min_protegido)
					{
						CHAVEPROT[i].Icc_2f_min_protegido = TRAFOS_DISTRI[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc2f_min;
						printf("CH %d Icc_2ph = %f TR = %d \n", i, CHAVEPROT[i].Icc_2f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho);
					}
					if (TRAFOS_DISTRI[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc1f_min < CHAVEPROT[i].Icc_1f_min_protegido)
					{
						CHAVEPROT[i].Icc_1f_min_protegido = TRAFOS_DISTRI[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc1f_min;
						printf("CH %d Icc_1ph = %f TR = %d \n", i, CHAVEPROT[i].Icc_1f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho);
					}
				}
				else if (CHAVEPROT[i].STRUCTFILHOSCH[j].TiposFilhosCH == "DJ")
				{
					if (DISJUNTORPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].STRUCTFILHOSDJ.size() == 0)
					{
						if (DISJUNTORPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc2f_min < CHAVEPROT[i].Icc_2f_min_protegido)
						{
							CHAVEPROT[i].Icc_2f_min_protegido = DISJUNTORPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc2f_min;
							printf("CH %d Icc_2ph = %f DJ = %d \n", i, CHAVEPROT[i].Icc_2f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho);
						}
						if (DISJUNTORPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc1f_min < CHAVEPROT[i].Icc_1f_min_protegido)
						{
							CHAVEPROT[i].Icc_1f_min_protegido = DISJUNTORPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc1f_min;
							printf("CH %d Icc_1ph = %f DJ = %d \n", i, CHAVEPROT[i].Icc_1f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho);
						}
					}
					else
					{
						{
							aux_struct_CH = CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho;
							for (k = 0; k < DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ.size(); k++)
							{
								if (DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].TiposFilhosDJ == "CH")
								{

									if (CHAVEPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc2f_min < CHAVEPROT[i].Icc_2f_min_protegido)
									{

										CHAVEPROT[i].Icc_2f_min_protegido = CHAVEPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc2f_min;
										printf("CH %d Icc_2ph = %f DJ = %d, CH filho = %d \n", i, CHAVEPROT[i].Icc_2f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho, DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho);
									}
									if (CHAVEPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc1f_min < CHAVEPROT[i].Icc_1f_min_protegido)
									{
										CHAVEPROT[i].Icc_1f_min_protegido = CHAVEPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc1f_min;
										printf("CH %d Icc_1ph = %f DJ = %d, CH filho = %d \n", i, CHAVEPROT[i].Icc_1f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho, DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho);
									}
								}
								else if (DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].TiposFilhosDJ == "TR")
								{
									if (TRAFOS_DISTRI[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc2f_min < CHAVEPROT[i].Icc_2f_min_protegido)
									{
										CHAVEPROT[i].Icc_2f_min_protegido = TRAFOS_DISTRI[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc2f_min;
										printf("CH %d Icc_2ph = %f DJ = %d, TR filho = %d \n", i, CHAVEPROT[i].Icc_2f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho, DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho);
									}
									if (TRAFOS_DISTRI[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc1f_min < CHAVEPROT[i].Icc_1f_min_protegido)
									{
										CHAVEPROT[i].Icc_1f_min_protegido = TRAFOS_DISTRI[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc1f_min;
										printf("CH %d Icc_1ph = %f DJ = %d, TR filho = %d \n", i, CHAVEPROT[i].Icc_1f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho, DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho);
									}
								}
								else if (DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].TiposFilhosDJ == "DJ")
								{
									if (DISJUNTORPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc2f_min < CHAVEPROT[i].Icc_2f_min_protegido)
									{
										CHAVEPROT[i].Icc_2f_min_protegido = DISJUNTORPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc2f_min;
										printf("CH %d Icc_2ph = %f DJ = %d, DJ filho = %d \n", i, CHAVEPROT[i].Icc_2f_min_protegido, CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho, DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho);
									}
									if (DISJUNTORPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc1f_min < CHAVEPROT[i].Icc_1f_min_protegido)
									{
										CHAVEPROT[i].Icc_1f_min_protegido = DISJUNTORPROT[DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho].Icc1f_min;
										printf("CH %d Icc_1ph = %f DJ = %d, DJ filho = %d \n", i, CHAVEPROT[i].Icc_1f_min_protegido,DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho, DISJUNTORPROT[aux_struct_CH].STRUCTFILHOSDJ[k].Pos_struct_Filho);
									}
								}
							}
						}
					}
				}
			}
		}
		
	}

	//------------------------------------------------------------------------------------------------------------------
    // Ajuste das correntes do relé de fase (50) - Instantâneo
    //------------------------------------------------------------------------------------------------------------------

	double I_inst;
	int    aux_pos_filho, aux_ramo_filho_filho;

	for (i = 0; i < DISJUNTORPROT.size(); i++)
	{
		// ------------------- RELÉ ----------------------------
		Tap_crit_1 = const_k * DISJUNTORPROT[i].Icarga; // I_at_inst >= (3 a 8) * I_carga_max / RTC; Aqui ainda falta dividir por RTC		
		if (Coordenado_ou_seletivo == 2) // Caso seja apenas seletivo (nem toda proteção seletiva é coordenada)
		{
			Tap_crit_2 = 0.0;                               // Inicia com esse valor (zera a cada iteração)
			if (DISJUNTORPROT[i].STRUCTFILHOSDJ.size() == 0) // Caso o disjuntor não tenha nenhum filho
			{
				Tap_crit_2 = DISJUNTORPROT[i].Icc3f; // Curto-circuito 3f assimetrico
			}
			else
			{
				for (j = 0; j < DISJUNTORPROT[i].STRUCTFILHOSDJ.size(); j++) // Começa a busca pelo filho com maior nível de CC
				{
					if (Tap_crit_2 < Icc_3ph_As[Nj_renum[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Ramos_ord_FilhoDJ]] * I_base)// Verifica se Icc_3ph_As no outro filho é maior que o anterior
					{
						Tap_crit_2 = Icc_3ph_As[Nj_renum[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Ramos_ord_FilhoDJ]] * I_base; // Se sim, atualiza o valor 
					}
				}
			}
		}
		else // Modelo coordenado, procura o maior nível de curto-circuito entre os filhos, dos filhos do disjuntor, do menor tipo de curto (bifásico ou fase terra)
		{
			Tap_crit_2 = 99999999999;                               // Inicia com esse valor (reseta a cada iteração)
			if (DISJUNTORPROT[i].STRUCTFILHOSDJ.size() == 0) // Caso o disjuntor não tenha nenhum filho
			{
				Tap_crit_2 = DISJUNTORPROT[i].Icc2f_min;
			}
			else // Caso o disjuntor tenha filhos
			{
				for (j = 0; j < DISJUNTORPROT[i].STRUCTFILHOSDJ.size(); j++) // Começa a análise dos j filhos
				{
					if (DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "CH") // Caso o filho seja um elo-fusível
					{
						aux_pos_filho = DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho;

						if (CHAVEPROT[aux_pos_filho].STRUCTFILHOSCH.size() == 0) // Caso o filho não tenha filhos
						{
							if (CHAVEPROT[aux_pos_filho].Icc2f_min < Tap_crit_2) // Se for menor, substitui
							{
								Tap_crit_2 = CHAVEPROT[aux_pos_filho].Icc2f_min;
							}
							
						}
						else // Caso o filho tenha filhos, começa a procura pelo de menor Icc
						{
							for (k = 0; k < CHAVEPROT[aux_pos_filho].STRUCTFILHOSCH.size(); k++)
							{
								aux_ramo_filho_filho = CHAVEPROT[aux_pos_filho].STRUCTFILHOSCH[k].Ramos_ord_FilhoCH; // Será utilizado o ramo, pois é mais fácil para achar as Icc
								
								if ((Icc_2ph [Nj_renum[aux_ramo_filho_filho]] * I_base) < Tap_crit_2)
								{
									Tap_crit_2 = (Icc_2ph [Nj_renum[aux_ramo_filho_filho]] * I_base);
								}
							}
						}				
					}
					else if (DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "TR")
					{
						aux_pos_filho = DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho;
						if ( TRAFOS_DISTRI[aux_pos_filho].Icc2f_min < Tap_crit_2)
						{ 
							Tap_crit_2 = TRAFOS_DISTRI[aux_pos_filho].Icc2f_min; // Um transformador não tem filhos...
						}
					}
					else if (DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "DJ")
					{
						aux_pos_filho = DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho;

						if (DISJUNTORPROT [aux_pos_filho].STRUCTFILHOSDJ.size() == 0) // Caso o filho não tenha filhos
						{
							if (DISJUNTORPROT [aux_pos_filho].Icc2f_min < Tap_crit_2) // Se for maior, substitui
							{
								Tap_crit_2 = DISJUNTORPROT [aux_pos_filho].Icc2f_min;
							}
							
						}
						else // Caso o filho tenha filhos, começa a procura pelo de menor Icc
						{
							for (k = 0; k < DISJUNTORPROT [aux_pos_filho].STRUCTFILHOSDJ.size(); k++)
							{
								aux_ramo_filho_filho = DISJUNTORPROT [aux_pos_filho].STRUCTFILHOSDJ[k].Ramos_ord_FilhoDJ; // Será utilizado o ramo, pois é mais fácil para achar as Icc
								
								if ((Icc_2ph [Nj_renum[aux_ramo_filho_filho]] * I_base) < Tap_crit_2)
								{
									Tap_crit_2 = (Icc_2ph [Nj_renum[aux_ramo_filho_filho]] * I_base);
								}
							}
						}
					}
				}
			}
		}

		Tap_crit_1 = Tap_crit_1 / DISJUNTORPROT [i].RTC; // O tap é normalizado pela RTC
		Tap_crit_2 = Tap_crit_2 / DISJUNTORPROT [i].RTC;

		printf ("DJ %d - Icc_2ph_inst = %f\n (Apenas crit 2)", i, Tap_crit_2*DISJUNTORPROT [i].RTC);

		// Compara quais dos dois critérios é maior
		if (Tap_crit_1 > Tap_crit_2) 
		{
			DISJUNTORPROT [i].Tap_Instantaneo_fase = (Tap_crit_1);  
			DISJUNTORPROT [i].I_instantaneo        = (Tap_crit_1 * DISJUNTORPROT [i].RTC);
		}
		else
		{
			DISJUNTORPROT [i].Tap_Instantaneo_fase = (Tap_crit_2); 
			DISJUNTORPROT [i].I_instantaneo        = (Tap_crit_2 * DISJUNTORPROT [i].RTC);
		}
	}

	// ------------------- RELIGADOR ----------------------------
	for (i = 0; i < CHAVEPROT.size(); i++)
	{
		if (CHAVEPROT[i].TipoCH == 6) // verifica se é um religador
		{
			Tap_crit_1 = const_k * CHAVEPROT[i].Icarga; // I_at_inst >= (3 a 8) * I_carga_max / RTC; Aqui ainda falta dividir por RTC		
			if (Coordenado_ou_seletivo == 2) // Caso seja apenas seletivo (nem toda proteção seletiva é coordenada)
			{
				Tap_crit_2 = 0.0;                               // Inicia com esse valor (zera a cada iteração)
				if (CHAVEPROT[i].STRUCTFILHOSCH.size() == 0) // Caso o disjuntor não tenha nenhum filho
				{
					Tap_crit_2 = CHAVEPROT[i].Icc3f; // Curto-circuito 3f assimetrico
				}
				else
				{
					for (j = 0; j < CHAVEPROT[i].STRUCTFILHOSCH.size(); j++) // Começa a busca pelo filho com maior nível de CC
					{
						if (Tap_crit_2 < Icc_3ph_As[Nj_renum[CHAVEPROT[i].STRUCTFILHOSCH[j].Ramos_ord_FilhoCH]] * I_base)// Verifica se Icc_3ph_As no outro filho é maior que o anterior
						{
							Tap_crit_2 = Icc_3ph_As[Nj_renum[CHAVEPROT[i].STRUCTFILHOSCH[j].Ramos_ord_FilhoCH]] * I_base; // Se sim, atualiza o valor 
						}
					}
				}
			}
			else // Modelo coordenado, procura o maior nível de curto-circuito entre os filhos, dos filhos do disjuntor, do menor tipo de curto (bifásico ou fase terra)
			{
				Tap_crit_2 = 99999999999;                               // Inicia com esse valor (reseta a cada iteração)
				if (CHAVEPROT[i].STRUCTFILHOSCH.size() == 0) // Caso o disjuntor não tenha nenhum filho
				{
					Tap_crit_2 = CHAVEPROT[i].Icc2f_min;
				}
				else // Caso o disjuntor tenha filhos
				{
					for (j = 0; j < CHAVEPROT[i].STRUCTFILHOSCH.size(); j++) // Começa a análise dos j filhos
					{
						if (CHAVEPROT[i].STRUCTFILHOSCH[j].TiposFilhosCH == "CH") // Caso o filho seja um elo-fusível
						{
							aux_pos_filho = CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho;

							if (CHAVEPROT[aux_pos_filho].STRUCTFILHOSCH.size() == 0) // Caso o filho não tenha filhos
							{
								if (CHAVEPROT[aux_pos_filho].Icc2f_min < Tap_crit_2) // Se for menor, substitui
								{
									Tap_crit_2 = CHAVEPROT[aux_pos_filho].Icc2f_min;
								}
							
							}
							else // Caso o filho tenha filhos, começa a procura pelo de menor Icc
							{
								for (k = 0; k < CHAVEPROT[aux_pos_filho].STRUCTFILHOSCH.size(); k++)
								{
									aux_ramo_filho_filho = CHAVEPROT[aux_pos_filho].STRUCTFILHOSCH[k].Ramos_ord_FilhoCH; // Será utilizado o ramo, pois é mais fácil para achar as Icc
								
									if ((Icc_2ph [Nj_renum[aux_ramo_filho_filho]] * I_base) < Tap_crit_2)
									{
										Tap_crit_2 = (Icc_2ph [Nj_renum[aux_ramo_filho_filho]] * I_base);
									}
								}
							}				
						}
						else if (CHAVEPROT[i].STRUCTFILHOSCH[j].TiposFilhosCH == "TR")
						{
							aux_pos_filho = CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho;
							if ( TRAFOS_DISTRI[aux_pos_filho].Icc2f_min < Tap_crit_2)
							{ 
								Tap_crit_2 = TRAFOS_DISTRI[aux_pos_filho].Icc2f_min; // Um transformador não tem filhos...
							}
						}
						else if (CHAVEPROT[i].STRUCTFILHOSCH[j].TiposFilhosCH == "DJ")
						{
							aux_pos_filho = CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho;

							if (DISJUNTORPROT [aux_pos_filho].STRUCTFILHOSDJ.size() == 0) // Caso o filho não tenha filhos
							{
								if (DISJUNTORPROT [aux_pos_filho].Icc2f_min < Tap_crit_2) // Se for maior, substitui
								{
									Tap_crit_2 = DISJUNTORPROT [aux_pos_filho].Icc2f_min;
								}
							
							}
							else // Caso o filho tenha filhos, começa a procura pelo de menor Icc
							{
								for (k = 0; k < DISJUNTORPROT [aux_pos_filho].STRUCTFILHOSDJ.size(); k++)
								{
									aux_ramo_filho_filho = DISJUNTORPROT [aux_pos_filho].STRUCTFILHOSDJ[k].Ramos_ord_FilhoDJ; // Será utilizado o ramo, pois é mais fácil para achar as Icc
								
									if ((Icc_2ph [Nj_renum[aux_ramo_filho_filho]] * I_base) < Tap_crit_2)
									{
										Tap_crit_2 = (Icc_2ph [Nj_renum[aux_ramo_filho_filho]] * I_base);
									}
								}
							}
						}
					}
				}
			}

			Tap_crit_1 = Tap_crit_1 / CHAVEPROT [i].RTC; // O tap é normalizado pela RTC
			Tap_crit_2 = Tap_crit_2 / CHAVEPROT [i].RTC;

			printf ("CH %d - Icc_2ph_inst = %f\n (Apenas crit 2)", i, Tap_crit_2*CHAVEPROT [i].RTC);

			// Compara quais dos dois critérios é maior
			if (Tap_crit_1 > Tap_crit_2) 
			{
				CHAVEPROT [i].Tap_Instantaneo_fase = (Tap_crit_1);  
				CHAVEPROT [i].I_instantaneo        = (Tap_crit_1 * CHAVEPROT [i].RTC);
			}
			else
			{
				CHAVEPROT [i].Tap_Instantaneo_fase = (Tap_crit_2); 
				CHAVEPROT [i].I_instantaneo        = (Tap_crit_2 * CHAVEPROT [i].RTC);
			}
		}
	}

	/*for (i = 0; i < 795; i++)
	{
		printf ("Nj_renum = %d    Ramo_ord=  %d \n", Nj_renum [i], i);
	}*/
		 
	//------------------------------------------------------------------------------------------------------------------
    // Ajuste das correntes do relé de neutro (50) - Instantâneo
    //------------------------------------------------------------------------------------------------------------------

	for ( i = 0; i < DISJUNTORPROT.size (); i++)
	{
		Tap_crit_1 = K_desequilibrio * const_k * DISJUNTORPROT[i].Icarga; // I_at_inst >= (3 a 8) * I_desequilibrio / RTC; Aqui ainda falta dividir por RTC
		
		
		if (Coordenado_ou_seletivo == 2) // Caso seja apenas seletivo (nem toda proteção seletiva é coordenada)
		{
			Tap_crit_2 = 0.0;                                         // Inicia com esse valor (zera a cada iteração)
			if (DISJUNTORPROT[i].STRUCTFILHOSDJ.size() == 0) // Caso o disjuntor não tenha nenhum filho
			{
				Tap_crit_2 = DISJUNTORPROT[i].Icc1f; // Curto-circuito 1f assimetrico
			}
			else
			{
				for (j = 0; j < DISJUNTORPROT[i].STRUCTFILHOSDJ.size(); j++) // Começa a busca pelo filho com maior nível de CC
				{
					if (Tap_crit_2 < Icc_1ph_As[Nj_renum [DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Ramos_ord_FilhoDJ]] * I_base)// Verifica se Icc_3ph_As no outro filho é maior que o anterior
					{
						Tap_crit_2 = Icc_1ph_As[Nj_renum [DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Ramos_ord_FilhoDJ]] * I_base; // Se sim, atualiza o valor 
					}
				}
			}
		}
		else // Modelo coordenado, procura o maior nível de curto-circuito entre os filhos, dos filhos do disjuntor
		{
			Tap_crit_2 = 9999999999.9;                                         // Inicia com esse valor (zera a cada iteração)
			if (DISJUNTORPROT[i].STRUCTFILHOSDJ.size() == 0) // Caso o disjuntor não tenha nenhum filho
			{
				Tap_crit_2 = DISJUNTORPROT[i].Icc1f_min;
			}
			else // Caso o disjuntor tenha filhos
			{
				for (j = 0; j < DISJUNTORPROT[i].STRUCTFILHOSDJ.size(); j++) // Começa a análise dos j filhos
				{
					if (DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "CH") // Caso o filho seja um elo-fusível
					{
						aux_pos_filho = DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho;

						if (CHAVEPROT[aux_pos_filho].STRUCTFILHOSCH.size() == 0) // Caso o filho não tenha filhos
						{
							if (CHAVEPROT[aux_pos_filho].Icc1f_min < Tap_crit_2) // Se for maior, substitui
							{
								Tap_crit_2 = CHAVEPROT[aux_pos_filho].Icc1f_min;
							}
							
						}
						else // Caso o filho tenha filhos, começa a procura pelo de maior Icc
						{
							for (k = 0; k < CHAVEPROT[aux_pos_filho].STRUCTFILHOSCH.size(); k++)
							{
								aux_ramo_filho_filho = CHAVEPROT[aux_pos_filho].STRUCTFILHOSCH [k].Ramos_ord_FilhoCH; // Será utilizado o ramo, pois é mais fácil para achar as Icc
								
								if ((Icc_1ph_min [Nj_renum[aux_ramo_filho_filho]] * I_base) < Tap_crit_2)
								{
									Tap_crit_2 = (Icc_1ph_min [Nj_renum[aux_ramo_filho_filho]] * I_base);
								}
							}
						}				
					}
					else if (DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "TR")
					{
						aux_pos_filho = DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho;
						if ( TRAFOS_DISTRI[aux_pos_filho].Icc1f_min < Tap_crit_2)
						{ 
							Tap_crit_2 = TRAFOS_DISTRI[aux_pos_filho].Icc1f_min; // Um transformador não tem filhos...
						}
					}
					else if (DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "DJ")
					{
						aux_pos_filho = DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho;

						if (DISJUNTORPROT [aux_pos_filho].STRUCTFILHOSDJ.size() == 0) // Caso o filho não tenha filhos
						{
							if (DISJUNTORPROT [aux_pos_filho].Icc1f_min < Tap_crit_2) // Se for maior, substitui
							{
								Tap_crit_2 = DISJUNTORPROT [aux_pos_filho].Icc1f_min;
							}
							
						}
						else // Caso o filho tenha filhos, começa a procura pelo de maior Icc
						{
							for (k = 0; k < DISJUNTORPROT [aux_pos_filho].STRUCTFILHOSDJ.size(); k++)
							{
								aux_ramo_filho_filho = DISJUNTORPROT [aux_pos_filho].STRUCTFILHOSDJ[k].Ramos_ord_FilhoDJ; // Será utilizado o ramo, pois é mais fácil para achar as Icc
								
								if ((Icc_1ph_min [Nj_renum[aux_ramo_filho_filho]] * I_base) < Tap_crit_2)
								{
									Tap_crit_2 = (Icc_1ph_min [Nj_renum[aux_ramo_filho_filho]] * I_base);
								}
							}
						}
					}
				}
			}
		}

		Tap_crit_1 = Tap_crit_1 / DISJUNTORPROT [i].RTC; // O tap é normalizado pela RTC
		Tap_crit_2 = Tap_crit_2 / DISJUNTORPROT [i].RTC;

		printf ("DJ %d - Icc_1ph_inst = %f\n (Apenas crit 2)", i, Tap_crit_2*DISJUNTORPROT [i].RTC);

		// Compara quais dos dois critérios é maior
		if (Tap_crit_1 > Tap_crit_2) 
		{
			DISJUNTORPROT [i].Tap_Instantaneo_neutro = (Tap_crit_1);  
			DISJUNTORPROT [i].I_instantaneo_neutro   = (Tap_crit_1 * DISJUNTORPROT [i].RTC);
		}
		else
		{
			DISJUNTORPROT [i].Tap_Instantaneo_neutro = (Tap_crit_2); 
			DISJUNTORPROT [i].I_instantaneo_neutro   = (Tap_crit_2 * DISJUNTORPROT [i].RTC);
		}
	}	

	// ----------- RELIGADOR ---------------------
	for ( i = 0; i < CHAVEPROT.size (); i++)
	{
		if (CHAVEPROT[i].TipoCH == 6) // verifica se é um religador
		{
			Tap_crit_1 = K_desequilibrio * const_k * CHAVEPROT[i].Icarga; // I_at_inst >= (3 a 8) * I_desequilibrio / RTC; Aqui ainda falta dividir por RTC
			Tap_crit_2 = 0.0;                                         // Inicia com esse valor (zera a cada iteração)

			if (Coordenado_ou_seletivo == 2) // Caso seja apenas seletivo (nem toda proteção seletiva é coordenada)
			{
				if (CHAVEPROT[i].STRUCTFILHOSCH.size () == 0) // Caso o disjuntor não tenha nenhum filho
				{
					Tap_crit_2 = DISJUNTORPROT[i].Icc1f; // Curto-circuito 1f assimetrico
				}
				else
				{
					for (j = 0; j < CHAVEPROT[i].STRUCTFILHOSCH.size (); j++) // Começa a busca pelo filho com maior nível de CC
					{
						if (Tap_crit_2 < Icc_1ph_As[Nj_renum[CHAVEPROT[i].STRUCTFILHOSCH[j].Ramos_ord_FilhoCH]] * I_base)// Verifica se Icc_3ph_As no outro filho é maior que o anterior
						{
							Tap_crit_2 = Icc_1ph_As[Nj_renum[CHAVEPROT[i].STRUCTFILHOSCH[j].Ramos_ord_FilhoCH]] * I_base; // Se sim, atualiza o valor 
						}
					}
				}
			}
			else // Modelo coordenado, procura o maior nível de curto-circuito entre os filhos, dos filhos do religador
			{
				Tap_crit_2 = 999999999999.9;                                         // Inicia com esse valor (zera a cada iteração)
				if (CHAVEPROT[i].STRUCTFILHOSCH.size () == 0) // Caso o religador não tenha nenhum filho
				{
					Tap_crit_2 = CHAVEPROT[i].Icc1f;
				}
				else // Caso o disjuntor tenha filhos
				{
					for (j = 0; j < CHAVEPROT[i].STRUCTFILHOSCH.size (); j++) // Começa a análise dos j filhos
					{
						if (CHAVEPROT[i].STRUCTFILHOSCH[j].TiposFilhosCH == "CH") // Caso o filho seja um elo-fusível
						{
							aux_pos_filho = CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho;

							if (CHAVEPROT[aux_pos_filho].STRUCTFILHOSCH.size () == 0) // Caso o filho não tenha filhos
							{
								if (CHAVEPROT[aux_pos_filho].Icc1f_min < Tap_crit_2) // Se for maior, substitui
								{
									Tap_crit_2 = CHAVEPROT[aux_pos_filho].Icc1f_min;
								}

							}
							else // Caso o filho tenha filhos, começa a procura pelo de maior Icc
							{
								for (k = 0; k < CHAVEPROT[aux_pos_filho].STRUCTFILHOSCH.size (); k++)
								{
									aux_ramo_filho_filho = CHAVEPROT[aux_pos_filho].STRUCTFILHOSCH[k].Ramos_ord_FilhoCH; // Será utilizado o ramo, pois é mais fácil para achar as Icc

									if (( Icc_1ph_min[Nj_renum[aux_ramo_filho_filho]] * I_base ) < Tap_crit_2)
									{
										Tap_crit_2 = ( Icc_1ph_min[Nj_renum[aux_ramo_filho_filho]] * I_base );
									}
								}
							}
						}
						else if (CHAVEPROT[i].STRUCTFILHOSCH[j].TiposFilhosCH == "TR")
						{
							aux_pos_filho = CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho;
							if (TRAFOS_DISTRI[aux_pos_filho].Icc1f_min < Tap_crit_2)
							{
								Tap_crit_2 = TRAFOS_DISTRI[aux_pos_filho].Icc1f_min; // Um transformador não tem filhos...
							}
						}
						else if (CHAVEPROT[i].STRUCTFILHOSCH[j].TiposFilhosCH == "DJ")
						{
							aux_pos_filho = CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho;

							if (DISJUNTORPROT[aux_pos_filho].STRUCTFILHOSDJ.size () == 0) // Caso o filho não tenha filhos
							{
								if (DISJUNTORPROT[aux_pos_filho].Icc1f_min < Tap_crit_2) // Se for maior, substitui
								{
									Tap_crit_2 = DISJUNTORPROT[aux_pos_filho].Icc1f_min;
								}

							}
							else // Caso o filho tenha filhos, começa a procura pelo de maior Icc
							{
								for (k = 0; k < DISJUNTORPROT[aux_pos_filho].STRUCTFILHOSDJ.size (); k++)
								{
									aux_ramo_filho_filho = DISJUNTORPROT[aux_pos_filho].STRUCTFILHOSDJ[k].Ramos_ord_FilhoDJ; // Será utilizado o ramo, pois é mais fácil para achar as Icc

									if (( Icc_1ph_min[Nj_renum[aux_ramo_filho_filho]] * I_base ) < Tap_crit_2)
									{
										Tap_crit_2 = ( Icc_1ph_min[Nj_renum[aux_ramo_filho_filho]] * I_base );
									}
								}
							}
						}
					}
				}
			}

			Tap_crit_1 = Tap_crit_1 / CHAVEPROT[i].RTC; // O tap é normalizado pela RTC
			Tap_crit_2 = Tap_crit_2 / CHAVEPROT[i].RTC;

			printf ("CH %d - Icc_1ph_inst = %f\n (Apenas crit 2)", i, Tap_crit_2*CHAVEPROT [i].RTC);


			// Compara quais dos dois critérios é maior
			if (Tap_crit_1 > Tap_crit_2)
			{
				CHAVEPROT[i].Tap_Instantaneo_neutro = ( Tap_crit_1 );
				CHAVEPROT[i].I_instantaneo_neutro   = ( Tap_crit_1 * CHAVEPROT[i].RTC );
			}
			else
			{
				CHAVEPROT[i].Tap_Instantaneo_neutro = ( Tap_crit_2 );
				CHAVEPROT[i].I_instantaneo_neutro   = ( Tap_crit_2 * CHAVEPROT[i].RTC );
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------------------------
    // Coordenação Religador-fusível e Religador - Religador
    //------------------------------------------------------------------------------------------------------------------
	// Para todos os valores de curto-cicuito na zona de proteção do fusível, o tempo MÍNIMO de FUSÂO do mesmo deve ser MAIOR
	// que o tempo de abertura do religador - curva rápida- multiplicada por um fator k. 
	// T_fusão > k*tempo_abertura_rápida
	// Este falor k:1,2 para 1 operação rápida; k:1.5 para 2 operações ráidas.
	// O tempo MÁXIMO de INTERRUPÇÃO do elo fusível deve ser MENOR que o tempo mínimo de abertura do religador na curva retardada
	// T_interrupçãp < T_abertura_retardada

	aux_verifica_filhos_DJ          = 0;
	aux_verifica_filhos_religadores = 0;
	seletivo                        = 0;
	seletivo_neutro                 = 0;
	aux_Dial                        = 999.9;
    aux_Dial_neutro                 = 999.9;
	int aux_fusivel_2;
	int aux_alguma_coord, aux_alguma_coord_neutro = 0;
	float T_curva_rapida;	

	for ( i =  CHAVEPROT.size () - 1 ; i > - 1; i -- ) // Primeiro será coordenado com o maior fusível (se houver) depois, coordena com o religador
	{
		aux_menor_intervalo        = 999;
		aux_menor_intervalo_neutro = 999;
		aux_alguma_coord           = 0;
		aux_alguma_coord_neutro    = 0;

		if ( CHAVEPROT [i].TipoCH == 6 ) // Verifica se o dispositivo de retaguarda (protegido) é um religador
		{
			for ( k = 0; k < CHAVEPROT [i].STRUCTFILHOSCH.size (); k++)
			{
				if (CHAVEPROT [i].STRUCTFILHOSCH [k].TiposFilhosCH != "TR") // No momento, não coordena com os fusiveis do trafo
				{
					if ( CHAVEPROT [i].STRUCTFILHOSCH [k].TiposFilhosCH == "DJ" )
					{
						printf ("Erro, coordenação entre religador e disjuntor (incomplete)");
						break;
					}
					else if (CHAVEPROT [i].STRUCTFILHOSCH [k].TipoChave ==  6) // Caso o filho seja um religador
					{
						Intervalo_Coord        = Intervalo_Coord_rele_religador; 
						Ramo_protecao_primaria = CHAVEPROT [i].STRUCTFILHOSCH [k].Ramos_ord_FilhoCH;
						
						aux_Icc_min            = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc2f_min;        // Valores em [A]  
						aux_IccMax             = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc3f;            // Valores em [A]
						aux_Ipickup_fase       = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Ipickup_fase;

						printf ("Religador %d com a struct %d IccMin\n", i, k, aux_Icc_min);

						for (j1 = 0; j1 < CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH.size (); j1++)
						{
							if (j1 == 0)
							{
								Ramo_menor_icc_prot_primaria = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].Ramos_ord_FilhoCH;
								aux_Icc_min                  = CHAVEPROT [Ramo_menor_icc_prot_primaria].Icc2f_min;
							}
							else
							{
								Ramo_menor_icc_prot_primaria = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].Ramos_ord_FilhoCH;
								aux_Icc_min                  = CHAVEPROT [Ramo_menor_icc_prot_primaria].Icc2f_min;
							}
						}

						printf ("Religador %d com a struct %d IccMin\n", i, k, aux_Icc_min);

						aux_Icc_min_neutro     = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f_min; // Valores em [A]  
						aux_IccMax_neutro      = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f;            // Valores em [A]
						aux_delta_Icc_neutro   = (abs (aux_IccMax_neutro) - abs(aux_Icc_min_neutro)) / (aux_intervalo -1);          // Tamanho do passso da amostragem da corrente para o cálculo dos delta
						aux_Ipickup_neutro     = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Ipickup_neutro;

						for ( j = 0; j < aux_intervalo; j++) // A proteção primária (religador)
						{					           
							Icc_analisados             [j] = aux_Icc_min + j*aux_delta_Icc; //Vai ser criado x valores de Icc
							m_rele_aux_primaria            = Icc_analisados[j] / (CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Ipickup_fase);
							T_protecao_primaria[j]         = T_rele (CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Norma_Curva, CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Tipo_Curva, m_rele_aux_primaria, CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Dial_fase_retardada);

							Icc_analisados_neutro      [j] = aux_Icc_min_neutro + j*aux_delta_Icc_neutro; //Vai ser criado x valores de Icc
							m_rele_aux_primaria_neutro     = Icc_analisados_neutro [j] / (CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Ipickup_neutro);
							T_protecao_primaria_neutro [j] = T_rele (CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Norma_Curva, CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Tipo_Curva, m_rele_aux_primaria_neutro, CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Dial_neutro_retardada);
						}
					}
									
					else if ( CHAVEPROT [i].STRUCTFILHOSCH [k].TipoChave ==  0 && CHAVEPROT [i].STRUCTFILHOSCH [k].TiposFilhosCH == "CH") // Caso os filho seja uma Chave fusível
					{		
						Intervalo_Coord        = Intervalo_Coord_religador_fusivel;
						Ramo_protecao_primaria = CHAVEPROT [i].STRUCTFILHOSCH [k].Ramos_ord_FilhoCH;

						aux_Icc_min            = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc2f_min; // Valores em [A]  
						aux_IccMax             = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc3f;     // Valores em [A]
						aux_Ipickup_fase       = CHAVEPROT [i].Religador_Ipickup_fase;


				    	/*printf ("Religador %d com a struct %d IccMin %f\n", i, k, aux_Icc_min);*/

						if (CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH.size () > 0) // Caso a proteção primária tenha filhos
						{
							Ramo_menor_icc_prot_primaria = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].Ramos_ord_FilhoCH;

							if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].TiposFilhosCH == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								aux_Icc_min = CHAVEPROT [IndexStructCH [Ramo_menor_icc_prot_primaria]].Icc2f_min;
								/*printf ("Religador %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min);*/
							}
							else if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].TiposFilhosCH == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								/*aux_Icc_min = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc2f_min;*/
								aux_Icc_min = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc2f_min;
								/*printf ("Religador %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min);*/
							}
							else
							{
								aux_Icc_min = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc2f_min;
								/*printf ("Religador %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min);*/
							}						

							for (j1 = 1; j1 < CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH.size (); j1++) // Rotina para o cálculo do Icc mínimo da proteção primaria
							{
								Ramo_menor_icc_prot_primaria = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].Ramos_ord_FilhoCH;

								if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].TiposFilhosCH == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
								{
									aux_Icc_min_aux = CHAVEPROT [IndexStructCH [Ramo_menor_icc_prot_primaria]].Icc2f_min;
									/*printf ("Religador %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min);*/
								}
								else if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].TiposFilhosCH == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
								{
									/*aux_Icc_min_aux = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc2f_min;*/
									aux_Icc_min_aux = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc2f_min;
									/*printf ("Religador %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min);*/
								}
								else
								{
									aux_Icc_min_aux = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc2f_min;
									/*printf ("Religador %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min);*/
								}
								if ( aux_Icc_min_aux < aux_Icc_min) // Caso o valor do filho seja menor do que o anterior...atualiza
								{
									aux_Icc_min = aux_Icc_min_aux;
								}
							}
						}
						
						aux_delta_Icc    = (abs (aux_IccMax) - abs(aux_Icc_min)) / (aux_intervalo - 1);
						/*printf ("Icc mínimo [fase] %f\n", aux_Icc_min);
						printf ("----\n");*/

						aux_Icc_min_neutro = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f_min; // Valores em [A]  
						aux_IccMax_neutro  = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f;     // Valores em [A]
						aux_Ipickup_neutro = CHAVEPROT [i].Religador_Ipickup_neutro;

						/*printf ("[Neutro] Religador %d com a struct %d IccMin %f\n", i, k, aux_Icc_min_neutro);*/

						if (CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH.size () > 0) // Caso a proteção primária tenha filhos
						{
							Ramo_menor_icc_prot_primaria = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].Ramos_ord_FilhoCH;

							if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].TiposFilhosCH == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								aux_Icc_min_neutro = CHAVEPROT [IndexStructCH [Ramo_menor_icc_prot_primaria]].Icc1f_min;
								/*printf ("[Neutro] Religador %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min_neutro);*/
							}
							else if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].TiposFilhosCH == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								/*aux_Icc_min_neutro = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc1f_min;*/
								aux_Icc_min_neutro = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f_min;
								/*printf ("[Neutro] Religador %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min_neutro);*/
							}
							else
							{
								aux_Icc_min_neutro = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc1f_min;
								/*printf ("[Neutro] Religador %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min_neutro);*/
							}		

							for (j1 = 1; j1 < CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH.size (); j1++) // Rotina para o cálculo do Icc mínimo da proteção primaria
							{
								Ramo_menor_icc_prot_primaria = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].Ramos_ord_FilhoCH;

								if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].TiposFilhosCH == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
								{
									aux_Icc_min_neutro_aux = CHAVEPROT [IndexStructCH [Ramo_menor_icc_prot_primaria]].Icc1f_min;
									/*printf ("[Neutro] Religador %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min_aux);*/
								}
								else if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].TiposFilhosCH == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
								{
									/*aux_Icc_min_neutro_aux = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc1f_min;*/
									aux_Icc_min_neutro_aux = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f_min;
									/*printf ("[Neutro] Religador %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min_aux);*/
								}
								else
								{
									aux_Icc_min_neutro_aux = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc1f_min;
									/*printf ("[Neutro] Religador %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min_aux);*/
								}
								if ( aux_Icc_min_neutro_aux < aux_Icc_min_neutro) // Caso o valor do filho seja menor do que o anterior...atualiza
								{
									aux_Icc_min_neutro = aux_Icc_min_neutro_aux;
								}							
							}
						}
						 
						aux_delta_Icc_neutro = (abs (aux_IccMax_neutro) - abs(aux_Icc_min_neutro)) / (aux_intervalo - 1);
						printf ("----\n");

						//-------------------- Coordenação do dispotivo de Retaguarda -----------------------------
						for ( j = 0; j < aux_intervalo; j++) // A proteção primária no caso é feita por fusíveis
						{
							Icc_analisados        [j] = (aux_Icc_min        + j*aux_delta_Icc)        / 10.0; //Vai ser criado x valores de Iccs
							Icc_analisados_neutro [j] = (aux_Icc_min_neutro + j*aux_delta_Icc_neutro) / 10.0; //Vai ser criado x valores de Iccs
						}

						curvas_fusiveis (CHAVEPROT [i].STRUCTFILHOSCH [k].ValorElo, aux_intervalo, 1); // Esta rotina é usada para termos os valores dos tempos de Interrupção dos fusíveis
						
						for ( j = 0; j < aux_intervalo; j++) // A proteção primária no caso é feita por fusíveis
						{
							T_protecao_primaria        [j] = T_fusivel        [j];
							T_protecao_primaria_neutro [j] = T_fusivel_neutro [j];

							// Caso a corrente analisada de CC seja menor do que a nominal do fusivel
							if (T_protecao_primaria [j] < 0) // Quando isto acontece, não há coordenação entre os dispositivos
							{
								seletivo = 1;
								CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado = "Nao";
								printf("1-Não houve coordenacao do Religador %d com o filho %d\n", i, k);
							}
							if (T_protecao_primaria_neutro [j] < 0) // Quando isto acontece, não há coordenação entre os dispositivos
							{
								seletivo_neutro = 1;
								CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado_neutro = "Nao";
								printf("1-[Neutro] Não houve coordenacao do Religador %d com o filho %d\n", i, k);
							}
						}
					}// Termina o if se o filho é uma chave fusível ou religador

						//-- Ajustes da unidade temporizada		
						for ( j = 0; j < aux_intervalo; j++) //Calcula valores de corrente de acordo com o numero de pontos escolhidos e calcula os respectivos tempos dos relés
						{
							// Ajuste da proteção de retaguardada
							m_rele_aux                       = Icc_analisados        [j] / ( CHAVEPROT [i].Religador_Ipickup_fase   / 10.0);
							m_rele_aux_neutro                = Icc_analisados_neutro [j] / ( CHAVEPROT [i].Religador_Ipickup_neutro / 10.0 );
							T_protecao_retaguarda        [j] = T_rele (CHAVEPROT [i].Religador_Norma_Curva, CHAVEPROT [i].Religador_Tipo_Curva, m_rele_aux       , CHAVEPROT [i].Religador_Dial_fase_retardada);
							T_protecao_retaguarda_neutro [j] = T_rele (CHAVEPROT [i].Religador_Norma_Curva, CHAVEPROT [i].Religador_Tipo_Curva, m_rele_aux_neutro, CHAVEPROT [i].Religador_Dial_neutro_retardada);
						}
		
						for ( j = 0; j < aux_intervalo; j++)
						{
							Delta_T_protecao_retaguarda_primaria        [j] = T_protecao_retaguarda        [j] - T_protecao_primaria [j];
							Delta_T_protecao_retaguarda_primaria_neutro [j] = T_protecao_retaguarda_neutro [j] - T_protecao_primaria_neutro [j];

							// Ajuste de Fase
							aux_T_procurado = Intervalo_Coord - Delta_T_protecao_retaguarda_primaria [j] + T_protecao_retaguarda [j]; //Encontra qual o tempo necessário do rele para que o offest do TDS o faça ser seletivo
							m_rele_aux      = 10.0 * Icc_analisados [j] / ( CHAVEPROT [i].Religador_Ipickup_fase);
							aux_Dial        = Dial_rele (CHAVEPROT[i].Religador_Norma_Curva, CHAVEPROT[i].Religador_Tipo_Curva, m_rele_aux, aux_T_procurado);
							

							if (aux_Dial < 0) // Quando isto acontece, não há coordenação entre os dispositivos
							{
								CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado = "Nao";
								printf("Não houve coordenacao do Disjuntor %d com o filho %d\n", i, k);
							}

							if (aux_Dial > CHAVEPROT[i].Religador_Dial_fase_retardada) // Caso o dial do filho DJ analisado seja maior....
							{
								if (aux_Dial < Dial_max)
								{
									printf("[Fase] Aux Dial = %f do religador %d, filho: %d, Icc_max:%f, Icc_min:%f, Icc_coord: %f\n", aux_Dial, i, k, Icc_analisados[aux_intervalo-1]*10.0, Icc_analisados[0]*10.0,  Icc_analisados[j]*10.0);
									aux_alguma_coord                      = 1;
									CHAVEPROT[i].Religador_Dial_fase_retardada            = aux_Dial;   // Atualiza o valor do dial
									CHAVEPROT[i].Icc_coord_fase_min = aux_Icc_min;// Atualiza o valor no qual o relé está coordenado
									CHAVEPROT[i].Icc_coord_fase_max         = aux_IccMax;

									if (CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado != "Nao")
									{
										CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado = "Sim";
									}
								}
								else
								{
									CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado = "Nao";
									printf("Não houve coordenacao do Disjuntor %d com o filho %d\n", i, k);
								}
							}

							// Ajuste do Neutro	
							aux_T_procurado_neutro = Intervalo_Coord - Delta_T_protecao_retaguarda_primaria_neutro [j] + T_protecao_retaguarda_neutro [j]; //Encontra qual o tempo necessário do rele para que o offest do TDS o faça ser seletivo
							m_rele_aux_neutro      = 10.0 * Icc_analisados_neutro [j] / ( CHAVEPROT [i].Religador_Ipickup_neutro);
							aux_Dial_neutro        = Dial_rele (CHAVEPROT[i].Religador_Norma_Curva, CHAVEPROT[i].Religador_Tipo_Curva, m_rele_aux_neutro, aux_T_procurado_neutro);

							//printf("Disjuntor %d Filho %d Dial_aux %f\n", i, k, aux_Dial_neutro);

							if (aux_Dial_neutro < 0) // Quando isto acontece, não há coordenação entre os dispositivos
							{
								CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado_neutro = "Nao";
								printf("[Neutro] Não houve coordenacao do Disjuntor %d com o filho %d\n", i, k);
							}

							if (aux_Dial_neutro > CHAVEPROT[i].Religador_Dial_neutro_retardada) // Caso o dial do filho DJ analisado seja maior....
							{
								if (aux_Dial_neutro < Dial_max)
								{
									printf("[N] Aux Dial = %f do religador %d, filho: %d, Icc_max:%f, Icc_min:%f, Icc_coord: %f\n", aux_Dial, i, k, Icc_analisados_neutro[aux_intervalo-1]*10.0, Icc_analisados_neutro[0]*10.0,  Icc_analisados_neutro[j]*10.0);
									aux_alguma_coord_neutro                      = 1;
									CHAVEPROT[i].Religador_Dial_neutro_retardada = aux_Dial_neutro; // Atualiza o valor do dial
									CHAVEPROT[i].Icc_coord_neutro_min            = aux_Icc_min_neutro;// Atualiza o valor no qual o relé está coordenado
									CHAVEPROT[i].Icc_coord_neutro_max            = aux_IccMax_neutro;
									
									if (CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado_neutro != "Nao")
									{
										CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado_neutro = "Sim";
									}
								}
								else
								{
									CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado_neutro = "Nao";
									printf("[Neutro] Não houve coordenacao do Disjuntor %d com o filho %d\n [Excedeu Dial máx]", i, k);
								}
							}
						}

						Menor_Delta_T_protecao_retaguarda_primaria        = Delta_T_protecao_retaguarda_primaria        [0]; //inicializando
						Menor_Delta_T_protecao_retaguarda_primaria_neutro = Delta_T_protecao_retaguarda_primaria_neutro [0]; //inicializando
						aux_pos_menor_delta_T                             = 0;                                               //inicializando						
						aux_pos_menor_delta_T_neutro                      = 0;                                               //inicializando

						for ( j = 1; j < aux_intervalo; j++ ) // Verifica se os delta T sao maiores que o intervalo de coordenação (para serem seletivos)
						{
							if ( Menor_Delta_T_protecao_retaguarda_primaria > Delta_T_protecao_retaguarda_primaria [j]) // se o valor verificado é menor que o anterior
							{
								Menor_Delta_T_protecao_retaguarda_primaria = Delta_T_protecao_retaguarda_primaria [j];
								aux_pos_menor_delta_T = j;
							}

							if ( Menor_Delta_T_protecao_retaguarda_primaria_neutro > Delta_T_protecao_retaguarda_primaria_neutro [j]) // se o valor verificado é menor que o anterior
							{
								Menor_Delta_T_protecao_retaguarda_primaria_neutro = Delta_T_protecao_retaguarda_primaria_neutro [j];
								aux_pos_menor_delta_T_neutro = j;
							}
						}

						// Rotina para pegar o Icc min e máx, no caso do rele estiver coordenado com o dial mínimo
						if (Menor_Delta_T_protecao_retaguarda_primaria < aux_menor_intervalo && Menor_Delta_T_protecao_retaguarda_primaria > 0.0)
						{
							aux_menor_intervalo         = Menor_Delta_T_protecao_retaguarda_primaria;
							aux_icc_min_dial_min_trecho = aux_Icc_min;
							aux_icc_max_dial_min_trecho = aux_IccMax;
						}

						if (Menor_Delta_T_protecao_retaguarda_primaria_neutro < aux_menor_intervalo_neutro && Menor_Delta_T_protecao_retaguarda_primaria_neutro > 0.0)
						{
							aux_menor_intervalo_neutro         = Menor_Delta_T_protecao_retaguarda_primaria_neutro;
							aux_icc_min_dial_min_trecho_neutro = aux_Icc_min_neutro;
							aux_icc_max_dial_min_trecho_neutro = aux_IccMax_neutro;
						}

						if (i == 0)
						{
							Stop = 1;
						}

						if ( Menor_Delta_T_protecao_retaguarda_primaria > Intervalo_Coord ) // O tempo do religador deve ser maior que do fusivel
						{
							seletivo         = 1; // Já está coordenado c/ dial minimo (apenas uma flag)
							aux_alguma_coord = 1; // Apenas uma flag, que o dispositivo coordenou com algum dispositivo, mesmo que seja dial = dial_min
							if ( CHAVEPROT [i].STRUCTFILHOSCH [k].Coordenado != "Nao")
							{ 
								CHAVEPROT [i].STRUCTFILHOSCH [k].Coordenado = "Sim";
							}
							
						}

						if ( Menor_Delta_T_protecao_retaguarda_primaria_neutro > Intervalo_Coord ) // O tempo do religador deve ser maior que do fusivel
						{
							seletivo_neutro         = 1; // Já está coordenado c/ dial minimo (apenas uma flag)
							aux_alguma_coord_neutro = 1; // Apenas uma flag, que o dispositivo coordenou com algum dispositivo, mesmo que seja dial = dial_min
							if (CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado_neutro != "Nao")
							{
								CHAVEPROT [i].STRUCTFILHOSCH [k].Coordenado_neutro = "Sim";
							}
							
						}

						//if (seletivo == 0) // Caso o dial mínimo não seja suficiente
						//{							
						//	aux_T_procurado = Intervalo_Coord - Delta_T_protecao_retaguarda_primaria [aux_pos_menor_delta_T] + T_protecao_retaguarda [aux_pos_menor_delta_T]; //Encontra qual o tempo necessário do rele para que o offest do TDS o faça ser seletivo
						//	m_rele_aux      = 10.0 * Icc_analisados [aux_pos_menor_delta_T] / aux_Ipickup_fase;
						//	aux_Dial        = Dial_rele( CHAVEPROT[i].Religador_Norma_Curva, CHAVEPROT[i].Religador_Tipo_Curva, m_rele_aux, aux_T_procurado );

						//	if (aux_Dial < 0)// Quando isto acontece, não há coordenação entre os dispositivos
						//	{
						//		CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado = "Nao";
						//		printf("2-Não houve coordenacao do Religador %d com o filho %d\n", i, k);
						//	}

						//	if (aux_Dial > CHAVEPROT [i].Religador_Dial_fase_retardada)
						//	{
						//		if (aux_Dial < Dial_max)
						//		{
						//			aux_alguma_coord = 1; // Apenas uma flag, que o dispositivo coordenou com algum dispositivo, mesmo que seja dial = dial_min
						//			CHAVEPROT [i].Religador_Dial_fase_retardada = aux_Dial; // Atualiza na struct CHAVEPROT
						//			CHAVEPROT [i].Icc_2f_min_protegido          = aux_Icc_min;
						//			CHAVEPROT [i].Icc_3f_coord                  = aux_IccMax;

						//			if (CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado != "Nao")
						//			{
						//				CHAVEPROT [i].STRUCTFILHOSCH [k].Coordenado = "Sim";
						//			}									
						//		}
						//		else
						//		{
						//			CHAVEPROT [i].STRUCTFILHOSCH [k].Coordenado = "Nao";
						//			printf ("2-Não houve coordenacao do religador %d com o filho %d\n", i, k);
						//		}
						//	}			
						//}

						//if (seletivo_neutro == 0) // Caso o dial mínimo não seja suficiente
						//{							
						//	aux_T_procurado_neutro = Intervalo_Coord - Delta_T_protecao_retaguarda_primaria_neutro [aux_pos_menor_delta_T_neutro] + T_protecao_retaguarda_neutro [aux_pos_menor_delta_T_neutro]; //Encontra qual o tempo necessário do rele para que o offest do TDS o faça ser seletivo
						//	m_rele_aux_neutro      = 10.0 * Icc_analisados_neutro [aux_pos_menor_delta_T_neutro] / aux_Ipickup_neutro;
						//	aux_Dial_neutro        = Dial_rele (CHAVEPROT[i].Religador_Norma_Curva, CHAVEPROT[i].Religador_Tipo_Curva, m_rele_aux_neutro, aux_T_procurado_neutro);

						//	if (aux_Dial_neutro < 0) // Quando isto acontece, não há coordenação entre os dispositivos
						//	{
						//		CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado_neutro = "Nao";
						//		printf("2-[Neutro] Não houve coordenacao do Religador %d com o filho %d\n", i, k);
						//	}

						//	if (aux_Dial_neutro > CHAVEPROT [i].Religador_Dial_neutro_retardada)
						//	{
						//		if (aux_Dial_neutro < Dial_max)
						//		{
						//			aux_alguma_coord_neutro = 1; // Apenas uma flag, que o dispositivo coordenou com algum dispositivo, mesmo que seja dial = dial_min
						//			CHAVEPROT [i].Religador_Dial_neutro_retardada = aux_Dial_neutro; // Atualiza na struct CHAVEPROT
						//			CHAVEPROT [i].Icc_1f_min_protegido            = aux_Icc_min_neutro;
						//			CHAVEPROT [i].Icc_1f_coord                    = aux_IccMax_neutro;
						//			if (CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado_neutro != "Nao")
						//			{
						//				CHAVEPROT[i].STRUCTFILHOSCH[k].Coordenado_neutro = "Sim";
						//			}
						//		}
						//		else
						//		{
						//			CHAVEPROT [i].STRUCTFILHOSCH [k].Coordenado_neutro = "Nao";
						//			printf ("2-[Neutro] Não houve coordenacao do religador %d com o filho %d\n", i, k);
						//		}
						//	}
						//}						
						seletivo        = 0;
						seletivo_neutro = 0;

					//--------- Coordenação da curva rápida do religador (coordena apenas com fusivel) ------- AQUI CONSIDERA UMA CURVA INVERSA, MUITO INVERSA, COMO RÁPIDA. sERÁ DESCONSIDERADO, PQ A CURVA RÁPIDA PODE SER INST.

						//if (Coordenado_ou_seletivo == 2) // Caso seja seletivo
						//{
						//	// A corrente de curto circuito mínima é a própria corrente de curto-circuito mínima no filho
						//	// Lembrando que os valores das variaveis de curto-circuito (fora das struct) 

						//	aux_Icc_min          = Icc_3ph_As[CHAVEPROT [i].STRUCTFILHOSCH [k].Ramos_ord_FilhoCH] * I_base;	// Diferente para o sistema coordenado
						//	aux_Icc_min_neutro   = Icc_1ph_As[CHAVEPROT [i].STRUCTFILHOSCH [k].Ramos_ord_FilhoCH] * I_base;	// Diferente para o sistema coordenado
						//	aux_delta_Icc        = (abs (aux_IccMax)        - abs(aux_Icc_min))        / (aux_intervalo - 1);
						//	aux_delta_Icc_neutro = (abs (aux_IccMax_neutro) - abs(aux_Icc_min_neutro)) / (aux_intervalo - 1);
					
						//	for ( j = 0; j < aux_intervalo; j++) // A proteção primária no caso é feita por fusíveis
						//	{
						//		Icc_analisados        [j] = (aux_Icc_min        + j*aux_delta_Icc)        / 10.0; //Vai ser criado x valores de Iccs
						//		Icc_analisados_neutro [j] = (aux_Icc_min_neutro + j*aux_delta_Icc_neutro) / 10.0; //Vai ser criado x valores de Iccs
						//	}							
						//}

						//if ( CHAVEPROT [i].STRUCTFILHOSCH [k].TipoChave ==  0 && CHAVEPROT [i].STRUCTFILHOSCH [k].TiposFilhosCH == "CH") // Caso os filho seja uma Chave fusível
						//{
						//	for ( j = 0; j < aux_intervalo; j++) //Calcula valores de corrente de acordo com o numero de pontos escolhidos e calcula os respectivos tempos dos relés
						//	{
						//		m_rele_aux                       = Icc_analisados        [j] / ( CHAVEPROT [i].Religador_Ipickup_fase   / 10.0);
						//		m_rele_aux_neutro                = Icc_analisados_neutro [j] / ( CHAVEPROT [i].Religador_Ipickup_neutro / 10.0);
						//		T_protecao_retaguarda        [j] = T_rele ( CHAVEPROT [i].Religador_Norma_Curva, CHAVEPROT [i].Religador_Tipo_Curva, m_rele_aux       , CHAVEPROT [i].Religador_Dial_fase_rapida);
						//		T_protecao_retaguarda_neutro [j] = T_rele ( CHAVEPROT [i].Religador_Norma_Curva, CHAVEPROT [i].Religador_Tipo_Curva, m_rele_aux_neutro, CHAVEPROT [i].Religador_Dial_neutro_rapida);
						//	}
		
						//	curvas_fusiveis (CHAVEPROT [i].STRUCTFILHOSCH [k].ValorElo, aux_intervalo, 2); // Esta rotina é usada para termos os valores dos tempos de fusáo dos fusíveis

						//	// rotina para pegar o menor valor Deta_T
						//	for ( j = 0; j < aux_intervalo; j++)
						//	{
						//		T_protecao_primaria                         [j] = T_fusivel                  [j];
						//		T_protecao_primaria_neutro                  [j] = T_fusivel_neutro           [j];   
						//		Delta_T_protecao_retaguarda_primaria        [j] = T_protecao_primaria        [j] - T_protecao_retaguarda        [j] * K_religador;
						//		Delta_T_protecao_retaguarda_primaria_neutro [j] = T_protecao_primaria_neutro [j] - T_protecao_retaguarda_neutro [j] * K_religador;
						//	}

						//	Menor_Delta_T_protecao_retaguarda_primaria        = Delta_T_protecao_retaguarda_primaria        [0]; //inicializando
						//	Menor_Delta_T_protecao_retaguarda_primaria_neutro = Delta_T_protecao_retaguarda_primaria_neutro [0]; //inicializando
						//	aux_pos_menor_delta_T                             = 0; //inicializando
						//	aux_pos_menor_delta_T_neutro                      = 0; //inicializando

						//	for ( j = 1; j < aux_intervalo; j++) // Verifica se os delta T sao maiores que o intervalo de coordenação (para serem seletivos)
						//	{
						//		if ( Menor_Delta_T_protecao_retaguarda_primaria > Delta_T_protecao_retaguarda_primaria [j]) // se o valor verificado é menor que o anterior
						//		{
						//			Menor_Delta_T_protecao_retaguarda_primaria = Delta_T_protecao_retaguarda_primaria [j];
						//			aux_pos_menor_delta_T                      = j;
						//		}

						//		if ( Menor_Delta_T_protecao_retaguarda_primaria_neutro > Delta_T_protecao_retaguarda_primaria_neutro [j] ) // se o valor verificado é menor que o anterior
						//		{
						//			Menor_Delta_T_protecao_retaguarda_primaria_neutro = Delta_T_protecao_retaguarda_primaria_neutro [j];
						//			aux_pos_menor_delta_T_neutro                      = j;
						//		}
						//	}
						//	
						//	if ( Menor_Delta_T_protecao_retaguarda_primaria < Intervalo_Coord ) // Caso o tempo do rele, no dial minimo
						//	{
						//		seletivo = 1; // Já está coordenado c/ dial minimo (apenas uma flag)
						//		CHAVEPROT [i].Religador_Dial_fase_rapida    = Dial_min;
						//		CHAVEPROT [i].Abertura_Rapida_Coordenada    = "Nao";
						//		CHAVEPROT [i].STRUCTFILHOSCH [k].Coordenado = "Nao";
						//		printf ("RAPIDA-Falhou a cordenação do religador %d com o fusivel [Fase]%d\n", i, CHAVEPROT [i].STRUCTFILHOSCH [k].ValorElo);
						//	}

						//	if ( Menor_Delta_T_protecao_retaguarda_primaria_neutro < Intervalo_Coord ) // Caso o tempo do rele, no dial minimo
						//	{
						//		seletivo_neutro = 1; // Já está coordenado c/ dial minimo (apenas uma flag)
						//		CHAVEPROT [i].Religador_Dial_neutro_rapida         = Dial_min;
						//		CHAVEPROT [i].Abertura_Rapida_Coordenada_neutro    = "Nao";
						//		CHAVEPROT [i].STRUCTFILHOSCH [k].Coordenado_neutro = "Nao";
						//		printf ("RAPIDA-Falhou a cordenação do religador %d com o fusivel %d [Neutro]\n", i, CHAVEPROT [i].STRUCTFILHOSCH [k].ValorElo);
						//	}
						//	
						//	if (seletivo == 0) // Caso o dial mínimo não seja suficiente
						//	{
						//		aux_T_procurado  = Intervalo_Coord + Delta_T_protecao_retaguarda_primaria [aux_pos_menor_delta_T] + T_protecao_retaguarda [aux_pos_menor_delta_T] * K_religador; //Encontra qual o tempo necessário do rele para que o offest do TDS o faça ser seletivo
						//		m_rele_aux       = 10.0 * Icc_analisados [aux_pos_menor_delta_T] / (aux_Ipickup_fase); // o fator 10 é devido a formula utilizada
						//		aux_Dial         = Dial_rele ( CHAVEPROT [i].Religador_Norma_Curva, CHAVEPROT [i].Religador_Tipo_Curva, m_rele_aux, aux_T_procurado);

						//	}

						//	if (seletivo_neutro == 0) // Caso o dial mínimo não seja suficiente
						//	{
						//		aux_alguma_coord_neutro = 1;
						//		aux_T_procurado_neutro  = Intervalo_Coord + Delta_T_protecao_retaguarda_primaria_neutro [aux_pos_menor_delta_T_neutro] + T_protecao_retaguarda_neutro [aux_pos_menor_delta_T_neutro] * K_religador; //Encontra qual o tempo necessário do rele para que o offest do TDS o faça ser seletivo
						//		m_rele_aux_neutro       = 10.0 * Icc_analisados_neutro [aux_pos_menor_delta_T_neutro] / (aux_Ipickup_neutro); // o fator 10 é devido a formula utilizada
						//		aux_Dial_neutro         = Dial_rele ( CHAVEPROT [i].Religador_Norma_Curva, CHAVEPROT [i].Religador_Tipo_Curva, m_rele_aux_neutro, aux_T_procurado_neutro);
						//	}

						//	if ((aux_Dial < CHAVEPROT [i].Religador_Dial_fase_rapida) && seletivo == 0)
						//	{
						//		if ( aux_Dial < Dial_max)
						//		{
						//			CHAVEPROT [i].Religador_Dial_fase_rapida           = aux_Dial; // Atualiza na struct CHAVEPROT
						//			CHAVEPROT [i].Icc_2f_min_protegido                 = aux_Icc_min;
						//			CHAVEPROT [i].Icc_3f_coord                         = aux_IccMax;
						//			CHAVEPROT [i].STRUCTFILHOSCH [k].Coordenado_rapida = "Sim";
						//		}
						//		else
						//		{
						//			CHAVEPROT [i].STRUCTFILHOSCH [k].Coordenado_rapida = "Nao";
						//			printf ("Não houve coordenacao do religador %d com o filho %d [curva rapida]\n", i, k);
						//		}
						//	}

						//	seletivo  = 0;

						//	if ((aux_Dial_neutro < CHAVEPROT [i].Religador_Dial_neutro_rapida) && seletivo_neutro == 0)
						//	{
						//		if ( aux_Dial_neutro < Dial_max )
						//		{
						//			CHAVEPROT [i].Religador_Dial_neutro_rapida                = aux_Dial_neutro; // Atualiza na struct CHAVEPROT
						//			CHAVEPROT [i].Icc_1f_min_protegido                        = aux_Icc_min_neutro;
						//			CHAVEPROT [i].Icc_1f_coord                                = aux_IccMax_neutro;
						//			CHAVEPROT [i].STRUCTFILHOSCH [k].Coordenado_rapida_neutro = "Sim";
						//		}
						//		else
						//		{
						//			CHAVEPROT [i].STRUCTFILHOSCH [k].Coordenado_rapida_neutro = "Nao";
						//			printf ("[Neutro] Não houve coordenacao do religador %d com o filho %d [curva rapida]\n", i, k);
						//		}
						//	}

						//	seletivo_neutro         = 0;
						//	aux_alguma_coord        = 0;
						//	aux_alguma_coord_neutro = 0;
						//} // Finaliza a coordenação da curva rápida
					}
					
					// Caso o religador esteja coordenado com todos os dispostivos de proteção com o dial mínimo, sua faixa de coordenação será com o elemento que causou o menor delta T
					if ((CHAVEPROT [i].Religador_Dial_fase_retardada < (Dial_min + 0.01)) && (aux_Dial < Dial_max))
					{
						CHAVEPROT [i].Icc_2f_min_protegido = aux_icc_min_dial_min_trecho;
						CHAVEPROT [i].Icc_3f_coord         = aux_icc_max_dial_min_trecho;
					}
					if (CHAVEPROT[i].Religador_Dial_neutro_retardada < (Dial_min + 0.01) && (aux_Dial_neutro < Dial_max))
					{
						CHAVEPROT [i].Icc_1f_min_protegido = aux_icc_min_dial_min_trecho_neutro;
						CHAVEPROT [i].Icc_1f_coord         = aux_icc_max_dial_min_trecho_neutro;
					}

					// Caso o religador não coordene com nenhum dispositivo de proteção, deve-se adicionar o valor prórpio de icc
					if (aux_alguma_coord == 0)
					{
						CHAVEPROT [i].Icc_2f_min_protegido = CHAVEPROT [i].Icc2f_min;
						CHAVEPROT [i].Icc_3f_coord         = CHAVEPROT [i].Icc3f;
					}
					if (aux_alguma_coord_neutro == 0)
					{
						CHAVEPROT [i].Icc_1f_min_protegido = CHAVEPROT [i].Icc1f_min;
						CHAVEPROT [i].Icc_1f_coord         = CHAVEPROT [i].Icc1f;
					}

					// Caso houve coordenação, mas o dispositivo de proteção ficou com o dial mínimo, não é garantido que o intervalo de coordenação é o delta T de coordenação
					if (aux_alguma_coord == 1)
					{
						if (CHAVEPROT[i].Religador_Dial_fase_retardada < ( Dial_min + 0.001 ))
						{
							CHAVEPROT[i].Coordenado_dial_min = 1;
							printf ("O Religador %d esta coordenado com o dial min, nao e garantido o intervalo de coordenacao min\n", i);
						}
					}
					if (aux_alguma_coord_neutro == 1)
					{
						if (CHAVEPROT[i].Religador_Dial_neutro_retardada < ( Dial_min + 0.001 ))
						{
							CHAVEPROT[i].Coordenado_dial_min_neutro = 1;
							printf ("[Neutro] O Religador %d esta coordenado com o dial min, nao e garantido o intervalo de coordenacao min\n",i);
						}
					}
				}
			}
		}

	//------------------------------------------------------------------------------------------------------------------
    // Coordenação Relé-Relé e relé-religador e relé-fusível
    //------------------------------------------------------------------------------------------------------------------

    seletivo        = 0;    // caso essa variável seja igual a 1, o processo para porque já é seletivo
	seletivo_neutro = 0;    // caso essa variável seja igual a 1, o processo para porque já é seletivo

	for ( i = DISJUNTORPROT.size () - 1; i > - 1; i--) // Aqui será coordenado cada disjuntor com os fusíveis filhos
	{
		aux_menor_intervalo        = 999;
		aux_menor_intervalo_neutro = 999;
		aux_alguma_coord           = 0;
		aux_alguma_coord_neutro    = 0;

		for ( k = 0; k < DISJUNTORPROT [i].STRUCTFILHOSDJ.size (); k++)
		{
			Ramo_protecao_primaria = DISJUNTORPROT [i].STRUCTFILHOSDJ [k].Ramos_ord_FilhoDJ;

			if ( DISJUNTORPROT [i].STRUCTFILHOSDJ [k].TiposFilhosDJ == "DJ" || (DISJUNTORPROT [i].STRUCTFILHOSDJ [k].TiposFilhosDJ == "CH" )) // O DJ pai vai coordenando com cada filho DJ e/ou religadores
			{
				if (DISJUNTORPROT [i].STRUCTFILHOSDJ [k].TiposFilhosDJ == "DJ") // Caso o filho seja um DJ
				{
					Intervalo_Coord        = Intervalo_Coord_rele_rele;
					aux_Icc_min            = DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Icc2f_min; // icc mínimo do trecho protegido pelo rele/religador filho
					aux_IccMax             = DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Icc3f;           // icc máximo do trecho protegido pelo rele/religador filho
					aux_Ipickup_fase       = DISJUNTORPROT [i].Ipickup_fase;
					
					/*printf ("Rele %d com a struct %d IccMin %f\n", i, k, aux_Icc_min);*/

					if (DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ.size () > 0) // Caso a proteção primária tenha filhos
					{
						Ramo_menor_icc_prot_primaria = DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ [0].Ramos_ord_FilhoDJ;

						if ( DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ [0].TiposFilhosDJ == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
						{
							aux_Icc_min = CHAVEPROT [IndexStructCH [Ramo_menor_icc_prot_primaria]].Icc2f_min;
							/*printf ("Rele %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min);*/
						}
						else if ( DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ [0].TiposFilhosDJ == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
						{
							aux_Icc_min = DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Icc2f_min;
							/*aux_Icc_min = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc2f_min;

							printf ("Rele %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min);*/
						}
						else
						{
							aux_Icc_min = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc2f_min;
							/*printf ("Rele %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min);*/
						}						

						for (j1 = 1; j1 < DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ.size (); j1++) // Rotina para o cálculo do Icc mínimo da proteção primaria
						{
							Ramo_menor_icc_prot_primaria = DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ [j1].Ramos_ord_FilhoDJ;

							if ( DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ [j1].TiposFilhosDJ == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								aux_Icc_min_aux = CHAVEPROT [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc2f_min;
								/*printf ("Rele %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min_aux);*/
							}
							else if ( DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ [j1].TiposFilhosDJ == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								aux_Icc_min_aux = DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Icc2f_min;
								/*aux_Icc_min_aux = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc2f_min;
								printf ("Rele %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min_aux);*/
							}
							else
							{
								aux_Icc_min_aux = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc2f_min;
								/*printf ("Rele %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min_aux);*/
							}
							if (aux_Icc_min_aux < aux_Icc_min) // Caso o valor do filho seja menor do que o anterior...atualiza
							{
								aux_Icc_min = aux_Icc_min_aux;
							}
						}						
					}
					
					aux_delta_Icc    = (abs (aux_IccMax) - abs(aux_Icc_min)) / (aux_intervalo - 1);
					/*printf ("Icc mínimo [fase] %f\n", aux_Icc_min);
					printf ("----\n");*/

					aux_Icc_min_neutro = DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Icc1f_min; // icc mínimo do trecho protegido pelo rele/religador filho
					aux_IccMax_neutro  = DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Icc1f;     // icc máximo do trecho protegido pelo rele/religador filho
					aux_Ipickup_neutro = DISJUNTORPROT [i].Ipickup_neutro;

					/*printf ("[Neutro] Rele %d com a struct %d IccMin %f\n", i, k, aux_Icc_min);*/

					if (DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ.size () > 0) // Caso a proteção primária tenha filhos
					{
						Ramo_menor_icc_prot_primaria = DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ [0].Ramos_ord_FilhoDJ;

						if ( DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ [0].TiposFilhosDJ == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
						{
							aux_Icc_min_neutro = CHAVEPROT [IndexStructCH [Ramo_menor_icc_prot_primaria]].Icc1f_min;
							/*printf ("[Neutro] Rele %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min_neutro);*/
						}
						else if ( DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ [0].TiposFilhosDJ == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
						{
							aux_Icc_min_neutro = DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Icc1f_min;
							/*aux_Icc_min_neutro = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc1f_min;
							printf ("[Neutro] Rele %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min_neutro);*/
						}
						else
						{
							aux_Icc_min_neutro = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc1f_min;
							/*printf ("[Neutro] Rele %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min_neutro);*/
						}						

						for (j1 = 1; j1 < DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ.size (); j1++) // Rotina para o cálculo do Icc mínimo da proteção primaria
						{
							Ramo_menor_icc_prot_primaria = DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ [j1].Ramos_ord_FilhoDJ;

							if ( DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ [j1].TiposFilhosDJ == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								aux_Icc_min_neutro_aux = CHAVEPROT [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc1f_min;
								/*printf ("[Neutro] Rele %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min_aux);*/
							}
							else if ( DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].STRUCTFILHOSDJ [j1].TiposFilhosDJ == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								aux_Icc_min_neutro_aux = DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Icc1f_min;
								/*aux_Icc_min_neutro_aux = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc1f_min;
								printf ("[Neutro] Rele %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min_aux);*/
							}
							else
							{
								aux_Icc_min_neutro_aux = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc1f_min;
								/*printf ("[Neutro] Rele %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min_aux);*/
							}
							if (aux_Icc_min_neutro_aux < aux_Icc_min_neutro) // Caso o valor do filho seja menor do que o anterior...atualiza
							{
								aux_Icc_min_neutro = aux_Icc_min_neutro_aux;
							}
						}
					}					
					aux_delta_Icc_neutro = (abs (aux_IccMax_neutro) - abs(aux_Icc_min_neutro)) / (aux_intervalo - 1);
					/*printf ("Icc mínimo [neutro] %f\n", aux_Icc_min_neutro);
					printf ("----\n");*/
				}

				else if (DISJUNTORPROT [i].STRUCTFILHOSDJ [k].TipoChave == 6) // Caso o filho seja um religador
				{
					Intervalo_Coord  = Intervalo_Coord_rele_religador;
					aux_Icc_min      = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc2f_min; // icc mínimo do trecho protegido pelo rele/religador filho
					aux_IccMax       = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc3f;           // icc máximo do trecho protegido pelo rele/religador filho
					aux_Ipickup_fase = DISJUNTORPROT [i].Ipickup_fase;

					/*printf ("Rele %d com a struct %d IccMin %f\n", i, k, aux_Icc_min);*/

					if (CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH.size () > 0) // Caso a proteção primária tenha filhos
					{	
						Ramo_menor_icc_prot_primaria = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].Ramos_ord_FilhoCH;

						if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].TiposFilhosCH == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
						{
							aux_Icc_min = CHAVEPROT [IndexStructCH [Ramo_menor_icc_prot_primaria]].Icc2f_min;
							/*printf ("Rele %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min);*/
						}
						else if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].TiposFilhosCH == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
						{
							//aux_Icc_min =  CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc2f_min;
							aux_Icc_min = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc2f_min;
							//printf ("Rele %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min);*/
						}
						else
						{
							aux_Icc_min = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc2f_min;
							/*printf ("Rele %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min);*/
						}						

						for (j1 = 1; j1 < CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH.size (); j1++) // Rotina para o cálculo do Icc mínimo da proteção primaria
						{
							Ramo_menor_icc_prot_primaria = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].Ramos_ord_FilhoCH;

							if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].TiposFilhosCH == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								aux_Icc_min_aux = CHAVEPROT [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc2f_min;
								/*printf ("Rele %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min_aux);*/
							}
							else if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].TiposFilhosCH == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								//aux_Icc_min_aux = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc2f_min;
								aux_Icc_min_aux = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc2f_min;
								//printf ("Rele %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min_aux);*/
							}
							else
							{
								aux_Icc_min_aux = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc2f_min;
								/*printf ("Rele %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min_aux);*/
							}
							if (aux_Icc_min_aux < aux_Icc_min) // Caso o valor do filho seja menor do que o anterior...atualiza
							{
								aux_Icc_min = aux_Icc_min_aux;
							}
						}
					}

					aux_delta_Icc    = (abs (aux_IccMax) - abs(aux_Icc_min)) / (aux_intervalo - 1);
					/*printf ("Icc mínimo [fase] %f\n", aux_Icc_min);

					aux_Icc_min_neutro = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f_min; // icc mínimo do trecho protegido pelo rele/religador filho
					aux_IccMax_neutro  = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f;           // icc máximo do trecho protegido pelo rele/religador filho
					aux_Ipickup_neutro = DISJUNTORPROT [i].Ipickup_neutro;

					/*printf ("Rele %d com a struct %d IccMin %f\n", i, k, aux_Icc_min_neutro);*/

					if (CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH.size () > 0) // Caso a proteção primária tenha filhos
					{
						Ramo_menor_icc_prot_primaria = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].Ramos_ord_FilhoCH;

						if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].TiposFilhosCH == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
						{
							aux_Icc_min_neutro = CHAVEPROT [IndexStructCH [Ramo_menor_icc_prot_primaria]].Icc1f_min;
							/*printf ("[Neutro] Rele %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min_neutro);*/
						}
						else if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].TiposFilhosCH == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
						{
							//aux_Icc_min_neutro = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f_min;
							aux_Icc_min_neutro = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc1f_min;
							//printf ("[Neutro] Rele %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min_neutro);*/
						}
						else
						{
							aux_Icc_min_neutro = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc1f_min;
							/*printf ("[Neutro] Rele %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min_neutro);*/
						}						

						for (j1 = 1; j1 < CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH.size (); j1++) // Rotina para o cálculo do Icc mínimo da proteção primaria
						{
							Ramo_menor_icc_prot_primaria = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].Ramos_ord_FilhoCH;

							if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].TiposFilhosCH == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								aux_Icc_min_neutro_aux = CHAVEPROT [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc1f_min;
								/*printf ("[Neutro] Rele %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min_aux);*/
							}
							else if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].TiposFilhosCH == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								//aux_Icc_min_neutro_aux = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f_min;
								aux_Icc_min_neutro_aux = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc1f_min;
								//printf ("[Neutro] Rele %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min_aux);*/
							}
							else
							{
								aux_Icc_min_neutro_aux = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc1f_min;
								/*printf ("[Neutro] Rele %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min_aux);*/
							}
							if (aux_Icc_min_neutro < aux_Icc_min_neutro_aux) // Caso o valor do filho seja menor do que o anterior...atualiza
							{
								aux_Icc_min_neutro = aux_Icc_min_neutro_aux;
							}
						}
					}
					
					aux_delta_Icc_neutro = (abs (aux_IccMax_neutro) - abs(aux_Icc_min_neutro)) / (aux_intervalo - 1);
					/*printf ("Icc mínimo [neutro] %f\n", aux_Icc_min_neutro);	
					printf ("----\n");*/
				}

				else if (DISJUNTORPROT [i].STRUCTFILHOSDJ [k].TiposFilhosDJ == "CH") // Caso o filho seja uma Chave-fusivel
				{
					Intervalo_Coord   = Intervalo_Coord_rele_fusivel;
					aux_maior_fusivel = DISJUNTORPROT [i].STRUCTFILHOSDJ [k].ValorElo;		
					aux_Icc_min       = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc2f_min; // icc mínimo do trecho protegido pelo fusivel filho
					aux_IccMax        = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc3f;     // icc máximo do trecho protegido pelo fusivel filho
					aux_Ipickup_fase  = DISJUNTORPROT [i].Ipickup_fase;

					/*printf ("Rele %d com a struct %d IccMin %f\n", i, k, aux_Icc_min);*/

					if (CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH.size () > 0) // Caso a proteção primária tenha filhos
					{
						Ramo_menor_icc_prot_primaria = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].Ramos_ord_FilhoCH;

						if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].TiposFilhosCH == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
						{
							aux_Icc_min = CHAVEPROT [IndexStructCH [Ramo_menor_icc_prot_primaria]].Icc2f_min;
							/*printf ("Rele %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min);*/
						}
						else if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].TiposFilhosCH == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
						{
							//aux_Icc_min = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc2f_min;
							aux_Icc_min = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc2f_min;
							//printf ("Rele %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min);*/
						}
						else
						{
							aux_Icc_min = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc2f_min;
							/*printf ("Rele %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min);*/
						}						

						for (j1 = 1; j1 < CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH.size (); j1++) // Rotina para o cálculo do Icc mínimo da proteção primaria
						{
							Ramo_menor_icc_prot_primaria = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].Ramos_ord_FilhoCH;

							if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].TiposFilhosCH == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								aux_Icc_min_aux = CHAVEPROT [IndexStructCH [Ramo_menor_icc_prot_primaria]].Icc2f_min;
								/*printf ("Rele %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min_aux);*/
							}
							else if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].TiposFilhosCH == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								//aux_Icc_min_aux = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc2f_min;
								aux_Icc_min_aux = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc2f_min;
								//printf ("Rele %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min_aux);*/
							}
							else
							{
								aux_Icc_min_aux = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc2f_min;
								/*printf ("Rele %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min_aux);*/
							}
							if ( aux_Icc_min_aux < aux_Icc_min) // Caso o valor do filho seja menor do que o anterior...atualiza
							{
								aux_Icc_min = aux_Icc_min_aux;
							}
						}
					}

					aux_delta_Icc    = (abs (aux_IccMax) - abs(aux_Icc_min)) / (aux_intervalo - 1);
					/*printf ("Icc mínimo [fase] %f\n", aux_Icc_min);	
					printf ("----\n");*/
					
					aux_Icc_min_neutro = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f_min; // icc mínimo do trecho protegido pelo fusivel filho
					aux_IccMax_neutro  = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f;     // icc máximo do trecho protegido pelo fusivel filho
					aux_Ipickup_neutro = DISJUNTORPROT [i].Ipickup_neutro;
					
					/*printf ("[Neutro] Rele %d com a struct %d IccMin %f\n", i, k, aux_Icc_min_neutro);*/

					if (CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH.size () > 0) // Caso a proteção primária tenha filhos
					{
						Ramo_menor_icc_prot_primaria = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].Ramos_ord_FilhoCH;

						if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].TiposFilhosCH == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
						{
							aux_Icc_min_neutro = CHAVEPROT [IndexStructCH [Ramo_menor_icc_prot_primaria]].Icc1f_min;
							/*printf ("[Neutro] Rele %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min);*/
						}
						else if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [0].TiposFilhosCH == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
						{
							//aux_Icc_min_neutro = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f_min;
							aux_Icc_min_neutro = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc1f_min;
							//printf ("[Neutro] Rele %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min);*/
						}
						else
						{
							aux_Icc_min_neutro = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc1f_min;
							/*printf ("[Neutro] Rele %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min);*/
						}						

						for (j1 = 1; j1 < CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH.size (); j1++) // Rotina para o cálculo do Icc mínimo da proteção primaria
						{
							Ramo_menor_icc_prot_primaria = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].Ramos_ord_FilhoCH;

							if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].TiposFilhosCH == "CH") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								aux_Icc_min_neutro_aux = CHAVEPROT [IndexStructCH [Ramo_menor_icc_prot_primaria]].Icc1f_min;
								/*printf ("[Neutro] Rele %d com a struct %d IccMin %f [CH]\n", i, k, aux_Icc_min_neutro);*/
							}
							else if ( CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].STRUCTFILHOSCH [j1].TiposFilhosCH == "TR") // Caso o filho da prot. primaria seja um elo-fusivel
							{
								aux_Icc_min_neutro_aux = CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Icc1f_min;
								/*aux_Icc_min_neutro_aux = TRAFOS_DISTRI [IndexStruct [Ramo_menor_icc_prot_primaria]].Icc1f_min;
								printf ("[Neutro] Rele %d com a struct %d IccMin %f [TR]\n", i, k, aux_Icc_min_neutro);*/
							}
							else
							{
								aux_Icc_min_neutro_aux = DISJUNTORPROT [IndexStructDJ [Ramo_menor_icc_prot_primaria]].Icc1f_min;
								/*printf ("[Neutro] Rele %d com a struct %d IccMin %f [DJ]\n", i, k, aux_Icc_min_neutro);*/
							}
							if ( aux_Icc_min_neutro_aux < aux_Icc_min_neutro) // Caso o valor do filho seja menor do que o anterior...atualiza
							{
								aux_Icc_min_neutro = aux_Icc_min_neutro_aux;
							}
						}
					}

					aux_delta_Icc_neutro = (abs (aux_IccMax_neutro) - abs(aux_Icc_min_neutro)) / (aux_intervalo - 1);
					/*printf ("Icc mínimo [neutro] %f\n", aux_Icc_min_neutro);	
					printf ("----\n");*/
				}

				//-------------------- Coordenação do dispotivo de Retaguarda -----------------------------

				for ( j = 0; j < aux_intervalo; j++) //Calcula valores de corrente de acordo com o numero de pontos escolhidos e calcula os respectivos tempos dos relés
				{
					Icc_analisados        [j] = (aux_Icc_min        + j*aux_delta_Icc)        / 10.0;   //Vai ser criado x valores de Iccs
					Icc_analisados_neutro [j] = (aux_Icc_min_neutro + j*aux_delta_Icc_neutro) / 10.0;   //Vai ser criado x valores de Iccs

					if (DISJUNTORPROT [i].STRUCTFILHOSDJ [k].TipoChave == 6) // Caso o filho seja um religador
					{
						m_rele_aux_primaria            = Icc_analisados        [j] / (CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Ipickup_fase   / 10.0 );
						m_rele_aux_primaria_neutro     = Icc_analisados_neutro [j] / (CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Ipickup_neutro / 10.0);
						T_protecao_primaria        [j] = T_rele (CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Norma_Curva, CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Tipo_Curva, m_rele_aux_primaria       , CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Dial_fase_retardada);
						T_protecao_primaria_neutro [j] = T_rele (CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Norma_Curva, CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Tipo_Curva, m_rele_aux_primaria_neutro, CHAVEPROT [IndexStructCH [Ramo_protecao_primaria]].Religador_Dial_neutro_retardada);
					}
					else if (DISJUNTORPROT [i].STRUCTFILHOSDJ [k].TiposFilhosDJ == "DJ") // Caso o filho seja um DJ
					{
						m_rele_aux_primaria            = Icc_analisados        [j] / (DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Ipickup_fase   / 10.0);
						m_rele_aux_primaria_neutro     = Icc_analisados_neutro [j] / (DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Ipickup_neutro / 10.0);
						T_protecao_primaria        [j] = T_rele (DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Norma_Curva, DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Tipo_Curva, m_rele_aux_primaria       , DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Dial_fase);
						T_protecao_primaria_neutro [j] = T_rele (DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Norma_Curva, DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Tipo_Curva, m_rele_aux_primaria_neutro, DISJUNTORPROT [IndexStructDJ [Ramo_protecao_primaria]].Dial_neutro);
					}

					m_rele_aux                       = Icc_analisados        [j] / (DISJUNTORPROT [i].Ipickup_fase   / 10.0);
				    m_rele_aux_neutro                = Icc_analisados_neutro [j] / (DISJUNTORPROT [i].Ipickup_neutro / 10.0);
					T_protecao_retaguarda        [j] = T_rele (DISJUNTORPROT [i].Norma_Curva, DISJUNTORPROT [i].Tipo_Curva, m_rele_aux       , DISJUNTORPROT [i].Dial_fase);
					T_protecao_retaguarda_neutro [j] = T_rele (DISJUNTORPROT [i].Norma_Curva, DISJUNTORPROT [i].Tipo_Curva, m_rele_aux_neutro, DISJUNTORPROT [i].Dial_neutro);
				}

				if (DISJUNTORPROT [i].STRUCTFILHOSDJ [k].TipoChave == 0) // Pega os valores dos tempos da proteção primaria quando for fusivel
				{
					
					curvas_fusiveis (aux_maior_fusivel, aux_intervalo, 1); // Interrupção					

					for ( j = 0; j < aux_intervalo; j++)
					{
						T_protecao_primaria        [j] = T_fusivel        [j];
						T_protecao_primaria_neutro [j] = T_fusivel_neutro [j];

						// Caso a corrente analisada de CC seja menor do que a nominal do fusivel
						if (T_protecao_primaria [j] < 0) // Quando isto acontece, não há coordenação entre os dispositivos
						{
							seletivo = 1;
							DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado = "Nao";
							printf("Não houve coordenacao do Disjuntor %d com o filho %d\n", i, k);
						}
						if (T_protecao_primaria_neutro [j] < 0) // Quando isto acontece, não há coordenação entre os dispositivos
						{
							seletivo_neutro = 1;
							DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado_neutro = "Nao";
							printf("[Neutro] Não houve coordenacao do Disjuntor %d com o filho %d\n", i, k);
						}
					}
				}
		
				for ( j = 0; j < aux_intervalo; j++) // rotina para pegar o menor valor Deta_T
				{
					Delta_T_protecao_retaguarda_primaria        [j] = T_protecao_retaguarda        [j] - T_protecao_primaria        [j];
					Delta_T_protecao_retaguarda_primaria_neutro [j] = T_protecao_retaguarda_neutro [j] - T_protecao_primaria_neutro [j];

					if (k == 22)
					{
						Stop = 1;
					}
				
					// Ajuste de Fase
					aux_T_procurado = Intervalo_Coord - Delta_T_protecao_retaguarda_primaria [j] + T_protecao_retaguarda [j]; //Encontra qual o tempo necessário do rele para que o offest do TDS o faça ser seletivo
					m_rele_aux      = 10.0 * Icc_analisados [j] / ( DISJUNTORPROT [i].Ipickup_fase);
					aux_Dial        = Dial_rele (DISJUNTORPROT[i].Norma_Curva, DISJUNTORPROT[i].Tipo_Curva, m_rele_aux, aux_T_procurado);

					if (aux_Dial < 0) // Quando isto acontece, não há coordenação entre os dispositivos
					{
						DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado = "Nao";
						printf("Não houve coordenacao do Disjuntor %d com o filho %d\n", i, k);
					}
					
					if (aux_Dial > DISJUNTORPROT[i].Dial_fase) // Caso o dial do filho DJ analisado seja maior....
					{
						if (aux_Dial < Dial_max)
						{
							printf ("Disjuntor %d Filho %d Icc_min %f Icc_analisado %f Dial %f\n", i, k, aux_Icc_min, Icc_analisados [j]*10, aux_Dial);
							aux_alguma_coord                      = 1;
							DISJUNTORPROT[i].Dial_fase            = aux_Dial;   // Atualiza o valor do dial
							DISJUNTORPROT[i].Icc_coord_fase_min = aux_Icc_min;// Atualiza o valor no qual o relé está coordenado
							DISJUNTORPROT[i].Icc_coord_fase_max = aux_IccMax;

							if (DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado != "Nao")
							{
								DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado = "Sim";
							}
						}
						else
						{
							DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado = "Nao";
							printf("Não houve coordenacao do Disjuntor %d com o filho %d\n", i, k);
						}
					}

					// Ajuste do Neutro	
					aux_T_procurado_neutro = Intervalo_Coord - Delta_T_protecao_retaguarda_primaria_neutro [j] + T_protecao_retaguarda_neutro [j]; //Encontra qual o tempo necessário do rele para que o offest do TDS o faça ser seletivo
					m_rele_aux_neutro      = 10.0 * Icc_analisados_neutro [j] / ( DISJUNTORPROT [i].Ipickup_neutro);
					aux_Dial_neutro        = Dial_rele (DISJUNTORPROT[i].Norma_Curva, DISJUNTORPROT[i].Tipo_Curva, m_rele_aux_neutro, aux_T_procurado_neutro);

					//printf("Disjuntor %d Filho %d Dial_aux %f\n", i, k, aux_Dial_neutro);

					if (aux_Dial_neutro < 0) // Quando isto acontece, não há coordenação entre os dispositivos
					{
						DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado_neutro = "Nao";
						printf("[Neutro] Não houve coordenacao do Disjuntor %d com o filho %d\n", i, k);
					}

					if (aux_Dial_neutro > DISJUNTORPROT[i].Dial_neutro) // Caso o dial do filho DJ analisado seja maior....
					{
						if (aux_Dial_neutro < Dial_max)
						{
							printf ("Disjuntor %d Filho %d Icc_min %f Icc_coord %f Dial %f [N] \n", i, k, aux_Icc_min_neutro, Icc_analisados_neutro [j]*10.0, aux_Dial_neutro);
							aux_alguma_coord_neutro               = 1;
							DISJUNTORPROT[i].Dial_neutro          = aux_Dial_neutro; // Atualiza o valor do dial
							DISJUNTORPROT[i].Icc_coord_neutro_min = aux_Icc_min_neutro;// Atualiza o valor no qual o relé está coordenado
							DISJUNTORPROT[i].Icc_coord_neutro_max = aux_IccMax_neutro;
							
							if (DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado_neutro != "Nao")
							{
								DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado_neutro = "Sim";
							}
						}
						else
						{
							DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado_neutro = "Nao";
							printf("[Neutro] Não houve coordenacao do Disjuntor %d com o filho %d\n [Excedeu Dial máx]", i, k);
						}
					}
				}

				Menor_Delta_T_protecao_retaguarda_primaria        = Delta_T_protecao_retaguarda_primaria        [0]; //inicializando
				Menor_Delta_T_protecao_retaguarda_primaria_neutro = Delta_T_protecao_retaguarda_primaria_neutro [0]; //inicializando
				aux_pos_menor_delta_T        = 0; //inicializando
				aux_pos_menor_delta_T_neutro = 0; //inicializando

				for ( j = 1; j < aux_intervalo; j++) // Verifica se os delta T sao maiores que o intervalo de coordenação (para serem seletivos)
				{
					if ( Menor_Delta_T_protecao_retaguarda_primaria > Delta_T_protecao_retaguarda_primaria [j]) // se o valor verificado é menor que o anterior
					{
						Menor_Delta_T_protecao_retaguarda_primaria = Delta_T_protecao_retaguarda_primaria [j];
						aux_pos_menor_delta_T                      = j;
					}
					if ( Menor_Delta_T_protecao_retaguarda_primaria_neutro > Delta_T_protecao_retaguarda_primaria_neutro [j]) // se o valor verificado é menor que o anterior
					{
						Menor_Delta_T_protecao_retaguarda_primaria_neutro = Delta_T_protecao_retaguarda_primaria_neutro [j];
						aux_pos_menor_delta_T_neutro                      = j;
					}
				}

				if ( Menor_Delta_T_protecao_retaguarda_primaria >= Intervalo_Coord_rele_rele )
				{
					seletivo         = 1; // Já está coordenado c/ dial anterior (apenas uma flag)
					aux_alguma_coord = 1;
					if (DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado != "Nao")
					{
						DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado = "Sim";
					}
					
				}
				if ( Menor_Delta_T_protecao_retaguarda_primaria_neutro >= Intervalo_Coord_rele_rele )
				{
					seletivo_neutro         = 1; // Já está coordenado c/ dial anterior (apenas uma flag)
					aux_alguma_coord_neutro = 1;

					if (DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado_neutro != "Nao")
					{
						DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado_neutro = "Sim";
					}
				}

				// Rotina para pegar o Icc min e máx, no caso do rele estiver coordenado com o dial mínimo
				if (Menor_Delta_T_protecao_retaguarda_primaria < aux_menor_intervalo && Menor_Delta_T_protecao_retaguarda_primaria > 0.0)
				{
					aux_menor_intervalo         = Menor_Delta_T_protecao_retaguarda_primaria;
					aux_icc_min_dial_min_trecho = aux_Icc_min;
					aux_icc_max_dial_min_trecho = aux_IccMax;
				}
				if (Menor_Delta_T_protecao_retaguarda_primaria_neutro < aux_menor_intervalo_neutro && Menor_Delta_T_protecao_retaguarda_primaria_neutro > 0.0)
				{
					aux_menor_intervalo_neutro         = Menor_Delta_T_protecao_retaguarda_primaria_neutro;
					aux_icc_min_dial_min_trecho_neutro = aux_Icc_min_neutro;
					aux_icc_max_dial_min_trecho_neutro = aux_IccMax_neutro;
				}

		
				//if (seletivo == 0) // Caso o dial anterior não seja suficiente
				//{					
				//	aux_T_procurado = Intervalo_Coord - Delta_T_protecao_retaguarda_primaria [aux_pos_menor_delta_T] + T_protecao_retaguarda [aux_pos_menor_delta_T]; //Encontra qual o tempo necessário do rele para que o offest do TDS o faça ser seletivo
				//	m_rele_aux      = 10.0 * Icc_analisados [aux_pos_menor_delta_T] / ( DISJUNTORPROT [i].Ipickup_fase);
				//	aux_Dial        = Dial_rele (DISJUNTORPROT[i].Norma_Curva, DISJUNTORPROT[i].Tipo_Curva, m_rele_aux, aux_T_procurado);

				//	if (aux_Dial < 0) // Quando isto acontece, não há coordenação entre os dispositivos
				//	{
				//		DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado = "Nao";
				//		printf("Não houve coordenacao do Disjuntor %d com o filho %d\n", i, k);
				//	}

				//	if (aux_Dial > DISJUNTORPROT[i].Dial_fase) // Caso o dial do filho DJ analisado seja maior....
				//	{
				//		if (aux_Dial < Dial_max)
				//		{
				//			aux_alguma_coord                      = 1;
				//			DISJUNTORPROT[i].Dial_fase            = aux_Dial;   // Atualiza o valor do dial
				//			DISJUNTORPROT[i].Icc_2f_min_protegido = aux_Icc_min;// Atualiza o valor no qual o relé está coordenado
				//			DISJUNTORPROT[i].Icc_3f_coord         = aux_IccMax;
				//			if (DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado != "Nao")
				//			{
				//				DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado = "Sim";
				//			}
				//		}
				//		else
				//		{
				//			DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado = "Nao";
				//			printf("Não houve coordenacao do Disjuntor %d com o filho %d\n", i, k);
				//		}
				//	}
				//}
				
				//if (seletivo_neutro == 0) // Caso o dial mínimo não seja suficiente
				//{
				//	
				//	aux_T_procurado_neutro = Intervalo_Coord - Delta_T_protecao_retaguarda_primaria_neutro [aux_pos_menor_delta_T_neutro] + T_protecao_retaguarda_neutro [aux_pos_menor_delta_T_neutro]; //Encontra qual o tempo necessário do rele para que o offest do TDS o faça ser seletivo
				//	m_rele_aux_neutro      = 10.0 * Icc_analisados_neutro [aux_pos_menor_delta_T_neutro] / ( DISJUNTORPROT [i].Ipickup_neutro);
				//	aux_Dial_neutro        = Dial_rele (DISJUNTORPROT[i].Norma_Curva, DISJUNTORPROT[i].Tipo_Curva, m_rele_aux_neutro, aux_T_procurado_neutro);

				//	if (aux_Dial_neutro < 0) // Quando isto acontece, não há coordenação entre os dispositivos
				//	{
				//		DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado_neutro = "Nao";
				//		printf("[Neutro] Não houve coordenacao do Disjuntor %d com o filho %d\n", i, k);
				//	}

				//	if (aux_Dial_neutro > DISJUNTORPROT[i].Dial_neutro) // Caso o dial do filho DJ analisado seja maior....
				//	{
				//		if (aux_Dial_neutro < Dial_max)
				//		{
				//			aux_alguma_coord_neutro               = 1;
				//			DISJUNTORPROT[i].Dial_neutro          = aux_Dial_neutro; // Atualiza o valor do dial
				//			DISJUNTORPROT[i].Icc_1f_min_protegido = aux_Icc_min_neutro;// Atualiza o valor no qual o relé está coordenado
				//			DISJUNTORPROT[i].Icc_1f_coord         = aux_IccMax_neutro;
				//			
				//			if (DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado_neutro != "Nao")
				//			{
				//				DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado_neutro = "Sim";
				//			}
				//		}
				//		else
				//		{
				//			DISJUNTORPROT[i].STRUCTFILHOSDJ[k].Coordenado_neutro = "Nao";
				//			printf("[Neutro] Não houve coordenacao do Disjuntor %d com o filho %d\n", i, k);
				//		}
				//	}
				//}
				//printf ("Dial do disjuntor %d = %f\n",i,DISJUNTORPROT [i].Dial_fase);
			}

			else if (DISJUNTORPROT [i].STRUCTFILHOSDJ[k].TiposFilhosDJ == "TR") //Não cordena...apenas atualiza os valores da struct
			{
				aux_Icc_min        = TRAFOS_DISTRI [IndexStruct[DISJUNTORPROT [i].STRUCTFILHOSDJ[k].Ramos_ord_FilhoDJ]].Icc2f_min;
				aux_Icc_min_neutro = TRAFOS_DISTRI [IndexStruct[DISJUNTORPROT [i].STRUCTFILHOSDJ[k].Ramos_ord_FilhoDJ]].Icc1f_min;
			}	
			
			seletivo_neutro = 0; // Zeram as variáveis
			seletivo        = 0;
		}

		// Caso o Relé esteja coordenado com todos os dispostivos de proteção com o dial mínimo, sua faixa de coordenação será com o elemento que causou o menor delta T
		if (DISJUNTORPROT[i].Dial_fase < (Dial_min + 0.01))
		{
			DISJUNTORPROT[i].Icc_2f_min_protegido = aux_icc_min_dial_min_trecho;
			DISJUNTORPROT[i].Icc_3f_coord         = aux_icc_max_dial_min_trecho;
		}
		if (DISJUNTORPROT[i].Dial_neutro < (Dial_min + 0.01))
		{
			DISJUNTORPROT[i].Icc_1f_min_protegido = aux_icc_min_dial_min_trecho_neutro;
			DISJUNTORPROT[i].Icc_1f_coord         =	aux_icc_max_dial_min_trecho_neutro;
		}

		// Caso o religador não coordene com nenhum dispositivo de proteção, deve-se adicionar o valor prórpio de icc
		if (aux_alguma_coord == 0)
		{
			DISJUNTORPROT [i].Icc_2f_min_protegido = DISJUNTORPROT [i].Icc2f_min;
			DISJUNTORPROT [i].Icc_3f_coord         = DISJUNTORPROT [i].Icc3f;
		}
		if (aux_alguma_coord_neutro == 0)
		{
			DISJUNTORPROT [i].Icc_1f_min_protegido = DISJUNTORPROT [i].Icc1f_min;
			DISJUNTORPROT [i].Icc_1f_coord         = DISJUNTORPROT [i].Icc1f;
		}

		// Caso houve coordenação, mas o dispositivo de proteção ficou com o dial mínimo, não é garantido que o intervalo de coordenação é o delta T de coordenação
		if (aux_alguma_coord == 1)
		{
			if (DISJUNTORPROT[i].Dial_fase < ( Dial_min + 0.001 ))
			{
				DISJUNTORPROT[i].Coordenado_dial_min = 1;
				printf ("O disjuntor %d esta coordenado com o dial min, nao e garantido o intervalo de coordenacao min\n",i);
			}
		}
		if (aux_alguma_coord_neutro == 1)
		{
			if (DISJUNTORPROT[i].Dial_neutro < ( Dial_min + 0.001 ))
			{
				DISJUNTORPROT[i].Coordenado_dial_min_neutro = 1;
				printf ("[Neutro] O disjuntor %d esta coordenado com o dial min, nao e garantido o intervalo de coordenacao min\n",i);
			}
		}
	}
	
	Stop = 1;

	//------------------------------------------------------------------------------------------------------------------
    // Dados pro matlab (Rele)
    //------------------------------------------------------------------------------------------------------------------

	FILE    * pFile;
    pFile   = fopen ("Saida_Matlab_Rele.txt","w"); 

	int Ramo_Filho_Plot;
	fprintf (pFile, "Numero_DJ\n");
	fprintf (pFile, "%d\n", DISJUNTORPROT.size ());

	fprintf (pFile, " Indice  I_partida_fase  I_partida_neutro  Dial_fase  Dial_neutro  Norma_Curva Tipo_Curva Icc_2ph_min_protegido Icc_3ph Icc_1ph_min_protegido Icc_1ph\n");
	
	for ( i = 0; i < DISJUNTORPROT.size (); i++ )
	{		
		fprintf (pFile, " %8d %15.4f %15.4f %11.4f %11.4f %11d %11d %21.4f %11.2f %21.4f %11.2f\n", i, DISJUNTORPROT [i].Ipickup_fase, DISJUNTORPROT [i].Ipickup_neutro, DISJUNTORPROT [i].Dial_fase,
			     DISJUNTORPROT [i].Dial_neutro, DISJUNTORPROT [i].Norma_Curva, DISJUNTORPROT [i].Tipo_Curva, DISJUNTORPROT [i].Icc_coord_fase_min, DISJUNTORPROT [i].Icc_coord_fase_max, DISJUNTORPROT [i].Icc_coord_neutro_min, DISJUNTORPROT [i].Icc_coord_neutro_max );
	}

	fprintf (pFile, "\n DJ_pai Filho  Tipo_filho  Icc_1ph_min  Icc_1ph     Icc_2ph  Icc_3ph      I_partida_fase_filho  I_partida_neutro_filho  Dial_fase_filho  Dial_neutro_filho  Valor_Fusivel_Filho Norma_Curva Tipo_Curva  Coordenado? Coordenado_neutro?\n");
	
	for ( i = 0; i < DISJUNTORPROT.size (); i++ )
	{
		for ( j = 0; j < DISJUNTORPROT[i].STRUCTFILHOSDJ.size (); j++)
		{
			Ramo_Filho_Plot = DISJUNTORPROT[i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ;

			if (DISJUNTORPROT[i].STRUCTFILHOSDJ [j].TiposFilhosDJ == "CH")
			{
				if (DISJUNTORPROT[i].STRUCTFILHOSDJ [j].TipoChave == 0)
				{
					fprintf (pFile, " %4d %4d %12s %12.2f %9.2f %12.2f %12.2f                      0                      0                     0                     0 %12d                      0                     0                     %12s %12s\n", i, IndexStructCH [Ramo_Filho_Plot], DISJUNTORPROT [i].STRUCTFILHOSDJ [j].TiposFilhosDJ.c_str(),
						    CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc_coord_neutro_min, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc1f, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc_coord_fase_min,
							CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc3f, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].ValorElo, DISJUNTORPROT[i].STRUCTFILHOSDJ [j].Coordenado.c_str (), DISJUNTORPROT[i].STRUCTFILHOSDJ [j].Coordenado_neutro.c_str ());
				}
				else if (DISJUNTORPROT[i].STRUCTFILHOSDJ [j].TipoChave == 6)
				{
					fprintf (pFile, " %4d %4d %12s %12.2f %9.2f %12.2f %12.2f %15.2f %24.2f %20.2f %12.2f                     0                     %12d %12d %12s %12s\n", i, IndexStructCH [Ramo_Filho_Plot],  DISJUNTORPROT [i].STRUCTFILHOSDJ [j].TiposFilhosDJ.c_str(),
						    CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc_coord_neutro_min, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc1f, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc_coord_fase_min, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc3f, 
							CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Religador_Ipickup_fase, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Religador_Ipickup_neutro, CHAVEPROT[IndexStructCH [Ramo_Filho_Plot]].Religador_Dial_fase_retardada, CHAVEPROT[IndexStructCH [Ramo_Filho_Plot]].Religador_Dial_neutro_retardada, CHAVEPROT[IndexStructCH [Ramo_Filho_Plot]].Religador_Norma_Curva, CHAVEPROT[IndexStructCH [Ramo_Filho_Plot]].Religador_Tipo_Curva, DISJUNTORPROT[i].STRUCTFILHOSDJ [j].Coordenado.c_str (), DISJUNTORPROT[i].STRUCTFILHOSDJ [j].Coordenado_neutro.c_str ());
				}
			}
			else if ( DISJUNTORPROT[i].STRUCTFILHOSDJ [j].TiposFilhosDJ == "TR")
			{
				fprintf (pFile, " %4d %4d %12s %12.2f %9.2f %12.2f %12.2f                     0                     0                     0                     0 %12d                      0                     0                     %12s %12s\n", i, IndexStruct [Ramo_Filho_Plot], DISJUNTORPROT [i].STRUCTFILHOSDJ [j].TiposFilhosDJ.c_str(),
						    TRAFOS_DISTRI [IndexStruct [Ramo_Filho_Plot]].Icc1f_min, TRAFOS_DISTRI [IndexStruct [Ramo_Filho_Plot]].Icc1f, TRAFOS_DISTRI [IndexStruct [Ramo_Filho_Plot]].Icc2f_min, TRAFOS_DISTRI [IndexStruct [Ramo_Filho_Plot]].Icc3f, TRAFOS_DISTRI [IndexStruct [Ramo_Filho_Plot]].ValorElo, DISJUNTORPROT[i].STRUCTFILHOSDJ [j].Coordenado.c_str (), DISJUNTORPROT[i].STRUCTFILHOSDJ [j].Coordenado_neutro.c_str ());
			}
			
			else if ( DISJUNTORPROT[i].STRUCTFILHOSDJ [j].TiposFilhosDJ == "DJ")
			{
				fprintf (pFile, " %4d %4d %12s %12.2f %9.2f %12.2f %12.2f %15.2f %24.2f %20.2f %12.2f                     0                     %12d %12d %12s %12s\n", i, IndexStructDJ [Ramo_Filho_Plot], DISJUNTORPROT [i].STRUCTFILHOSDJ [j].TiposFilhosDJ.c_str(),
						    DISJUNTORPROT [IndexStructDJ [Ramo_Filho_Plot]].Icc_coord_neutro_min, DISJUNTORPROT [IndexStructDJ [Ramo_Filho_Plot]].Icc1f, DISJUNTORPROT [IndexStructDJ [Ramo_Filho_Plot]].Icc_coord_fase_min, DISJUNTORPROT [IndexStructDJ [Ramo_Filho_Plot]].Icc3f, 
							DISJUNTORPROT [IndexStructDJ [Ramo_Filho_Plot]].Ipickup_fase, DISJUNTORPROT [IndexStructDJ [Ramo_Filho_Plot]].Ipickup_neutro, DISJUNTORPROT[IndexStructDJ [Ramo_Filho_Plot]].Dial_fase, DISJUNTORPROT[IndexStructDJ [Ramo_Filho_Plot]].Dial_neutro, DISJUNTORPROT[IndexStructDJ [Ramo_Filho_Plot]].Norma_Curva, DISJUNTORPROT[IndexStructDJ [Ramo_Filho_Plot]].Tipo_Curva, DISJUNTORPROT[i].STRUCTFILHOSDJ [j].Coordenado.c_str (), DISJUNTORPROT[i].STRUCTFILHOSDJ [j].Coordenado_neutro.c_str ());
			}
			
		}
	}

	fclose (pFile); // Termina a função de escrita
	
	//------------------------------------------------------------------------------------------------------------------
    // Dados pro matlab (Religador)
    //------------------------------------------------------------------------------------------------------------------

    pFile   = fopen ("Saida_Matlab_Religador.txt","w"); 
	int Quantidade_Religadores = 0;

	for (i = 0; i < CHAVEPROT.size(); i++)
	{
		if (CHAVEPROT [i].TipoCH == 6)
		{
			Quantidade_Religadores = Quantidade_Religadores + 1; 
		}
	}

	fprintf (pFile, "Numero_Religador\n");
	fprintf (pFile, "%d\n", Quantidade_Religadores);
	//              .                      .                      .                      .                      .                      .                      .                      .                      .                      .                      .                      .
	fprintf (pFile, "       Indice              I_partida_fase         I_partida_neutro       Dial_fase_rapida    Dial_neutro_rapida      Dial_fase_retardada   Dial_neutro_retardada      Norma_Curva      Tipo_Curva         Icc_2ph_min_protegido Icc_3ph Icc_1ph_min_protegido  Icc_1ph\n");
	for ( i = 0; i < CHAVEPROT.size (); i++ )
	{		
		if (CHAVEPROT [i].TipoCH == 6)
		{
			fprintf (pFile, " %22d %22.2f %22.2f %22.2f %22.2f %22.2f %22.2f %22d %22d %22.4f %22.2f %22.4f %22.2f\n", i, CHAVEPROT [i].Religador_Ipickup_fase, CHAVEPROT [i].Religador_Ipickup_neutro,
				     CHAVEPROT [i].Religador_Dial_fase_rapida, CHAVEPROT [i].Religador_Dial_neutro_rapida, CHAVEPROT [i].Religador_Dial_fase_retardada, CHAVEPROT [i].Religador_Dial_neutro_retardada,
					 CHAVEPROT [i].Religador_Norma_Curva, CHAVEPROT [i].Religador_Tipo_Curva, CHAVEPROT [i].Icc_coord_fase_min, CHAVEPROT [i].Icc_coord_fase_max, CHAVEPROT [i].Icc_coord_neutro_min, CHAVEPROT [i].Icc_coord_neutro_max);
		}
	}

	//              .                      .                      .                      .                      .                      .                      .                      .                      .                      .                      .                      .                      .                      .                      .                      .
	fprintf (pFile, "\n       Religador_pai                  Filho            Tipo_filho             Icc_1ph_min               Icc_1ph                 Icc_2ph                Icc_3ph    I_partida_fase_filho  I_partida_N_filho     Dial_F_filho_retardada Dial_N_filho_retardada Dial_F_filho_rapida      Dial_N_filho_rapida    Valor_Fusivel_Filho  Norma_Curva Tipo_Curva  Coordenado? Coordenado_neutro?\n");
	
	for ( i = 0; i < CHAVEPROT.size (); i++ )
	{
		if (CHAVEPROT [i].TipoCH == 6)
		{
			for ( j = 0; j < CHAVEPROT[i].STRUCTFILHOSCH.size (); j++)
			{
				Ramo_Filho_Plot = CHAVEPROT[i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH;

				if (CHAVEPROT[i].STRUCTFILHOSCH [j].TiposFilhosCH == "CH")
				{
					if (CHAVEPROT[i].STRUCTFILHOSCH [j].TipoChave == 0)
					{
						fprintf (pFile, " %22d %22d %22s %22.2f %22.2f %22.2f %22.2f                     0                     0                     0                     0                     0                     0 %22d        0              0       %12s %12s\n", i, IndexStructCH [Ramo_Filho_Plot], CHAVEPROT [i].STRUCTFILHOSCH [j].TiposFilhosCH.c_str(),
								CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc_coord_neutro_min, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc1f, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc_coord_fase_min,
								CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc3f, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].ValorElo, CHAVEPROT[i].STRUCTFILHOSCH [j].Coordenado.c_str(), CHAVEPROT[i].STRUCTFILHOSCH [j].Coordenado_neutro.c_str());
					}
					else if (CHAVEPROT[i].STRUCTFILHOSCH [j].TipoChave == 6)
					{
						fprintf (pFile, " %22d %22d %22s %22.2f %22.2f %22.2f %22.2f %22.2f %22.2f %22.2f %22.2f  %22.2f %22.2f                      0 %22d %22d %12s %12s\n", i, IndexStructCH [Ramo_Filho_Plot], CHAVEPROT [i].STRUCTFILHOSCH [j].TiposFilhosCH.c_str(),
								CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc_coord_neutro_min, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc1f, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc_coord_fase_min, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Icc3f, 
								CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Religador_Ipickup_fase, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Religador_Ipickup_neutro, CHAVEPROT[IndexStructCH [Ramo_Filho_Plot]].Religador_Dial_fase_retardada, CHAVEPROT[IndexStructCH [Ramo_Filho_Plot]].Religador_Dial_neutro_retardada,
								CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Religador_Dial_fase_rapida, CHAVEPROT[IndexStructCH [Ramo_Filho_Plot]].Religador_Dial_neutro_rapida, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Religador_Norma_Curva, CHAVEPROT [IndexStructCH [Ramo_Filho_Plot]].Religador_Tipo_Curva, CHAVEPROT[i].STRUCTFILHOSCH [j].Coordenado.c_str(), CHAVEPROT[i].STRUCTFILHOSCH [j].Coordenado_neutro.c_str());
					}
				}
				else if (CHAVEPROT[i].STRUCTFILHOSCH [j].TiposFilhosCH == "TR")
				{
					fprintf (pFile, " %22d %22d %22s %22.2f %22.2f %22.2f %22.2f                     0                     0                     0                     0                     0                     0 %22d                      0                     0                     %12s %12s\n", i, IndexStruct [Ramo_Filho_Plot], CHAVEPROT [i].STRUCTFILHOSCH [j].TiposFilhosCH.c_str(),
								TRAFOS_DISTRI [IndexStruct [Ramo_Filho_Plot]].Icc1f_min, TRAFOS_DISTRI [IndexStruct [Ramo_Filho_Plot]].Icc1f, TRAFOS_DISTRI [IndexStruct [Ramo_Filho_Plot]].Icc2f_min, TRAFOS_DISTRI [IndexStruct [Ramo_Filho_Plot]].Icc3f, TRAFOS_DISTRI [IndexStruct [Ramo_Filho_Plot]].ValorElo, CHAVEPROT[i].STRUCTFILHOSCH [j].Coordenado.c_str(), CHAVEPROT[i].STRUCTFILHOSCH [j].Coordenado_neutro.c_str());
				}
			
				else if (CHAVEPROT[i].STRUCTFILHOSCH [j].TiposFilhosCH == "DJ")
				{
					fprintf (pFile, " %22d %22d %22s %22.2f %22.2f %22.2f %22.2f %22.2f %22.2f %22.2f %22.2f                     0                     0                     0  %22d %22d %12s %12s\n", i, IndexStructDJ [Ramo_Filho_Plot], CHAVEPROT [i].STRUCTFILHOSCH [j].TiposFilhosCH.c_str(),
								DISJUNTORPROT [IndexStructDJ [Ramo_Filho_Plot]].Icc_coord_neutro_min, DISJUNTORPROT [IndexStructDJ [Ramo_Filho_Plot]].Icc1f, DISJUNTORPROT [IndexStructDJ [Ramo_Filho_Plot]].Icc_coord_fase_min, DISJUNTORPROT [IndexStructDJ [Ramo_Filho_Plot]].Icc3f, 
								DISJUNTORPROT [IndexStructDJ [Ramo_Filho_Plot]].Ipickup_fase, DISJUNTORPROT [IndexStructDJ [Ramo_Filho_Plot]].Ipickup_neutro, DISJUNTORPROT[IndexStructDJ [Ramo_Filho_Plot]].Dial_fase, DISJUNTORPROT[IndexStructDJ [Ramo_Filho_Plot]].Dial_neutro, DISJUNTORPROT[IndexStructDJ [Ramo_Filho_Plot]].Norma_Curva, DISJUNTORPROT[IndexStructDJ [Ramo_Filho_Plot]].Tipo_Curva, CHAVEPROT[i].STRUCTFILHOSCH [j].Coordenado.c_str(), CHAVEPROT[i].STRUCTFILHOSCH [j].Coordenado_neutro.c_str());
				}			
			}
		}
	}

	fclose (pFile); // Termina a função de escrita

} // Finaliza a função toda

void Calculo_do_fluxo::curvas_fusiveis (int maior_fusivel, int intervalo, int curva_fusao_interrupcao) 
{
	float indice_k;
	float indice_p;
	float indice_d;
	float indice_g;
	float M_fusivel;
	float M_fusivel_neutro;

	if (curva_fusao_interrupcao == 2) // caso o valor procurado seja de fusão
		{
		// Valores de fusão
		if (maior_fusivel == 6)
		{
			indice_k = 120.0;
			indice_p = 2.05;
			indice_d = 0.05;
			indice_g = 1.5;
		}
		else if (maior_fusivel == 10)
		{
			indice_k = 250.0;
			indice_p = 2.01;
			indice_d = 0.073;
			indice_g = 4.5;
		}
		else if (maior_fusivel == 15)
		{
			indice_k = 250.0;
			indice_p = 1.9;
			indice_d = 0.12;
			indice_g = 9.0;

		}
		else if (maior_fusivel == 25)
		{
			indice_k = 320.0;
			indice_p = 2.01;
			indice_d = 0.45;
			indice_g = 28.5;

		}
		else if (maior_fusivel == 40)
		{
			indice_k = 320.0;
			indice_p = 2.0;
			indice_d = 1.08;
			indice_g = 76.5;

		}
		else if (maior_fusivel == 65)
		{
			indice_k = 370.0;
			indice_p = 2.0;
			indice_d = 4.0;
			indice_g = 265.8;

		}
		else if (maior_fusivel == 100)
		{
			indice_k = 1200.0;
			indice_p = 2.03;
			indice_d = 2.05;
			indice_g = 500.0;

		}
		else if (maior_fusivel == 140)
		{
			indice_k = 1200.0;
			indice_p = 2.0;
			indice_d = 5.1;
			indice_g = 1300.0;

		}
		else if (maior_fusivel == 200)
		{
			indice_k = 2080.0;
			indice_p = 2.1;
			indice_d = 14.3;
			indice_g = 6400.0;

		}
		else
		{
			printf ("Fusivel não coordena com o relé\n");
		}
	}
	else // caso seja de Interrupção
	{
		// Valores de Interrupção
		if (maior_fusivel == 6)
		{
			indice_k = 200.0;
			indice_p = 2.1;
			indice_d = 0.056;
			indice_g = 2.4;
		}
		else if (maior_fusivel == 10)
		{
			indice_k = 250.0;
			indice_p = 2.01;
			indice_d = 0.11;
			indice_g = 6.5;
		}
		else if (maior_fusivel == 15)
		{
			indice_k = 250.0;
			indice_p = 1.9;
			indice_d = 0.2;
			indice_g = 14.0;

		}
		else if (maior_fusivel == 25)
		{
			indice_k = 320.0;
			indice_p = 2.0;
			indice_d = 0.66;
			indice_g = 40.5;

		}
		else if (maior_fusivel == 40)
		{
			indice_k = 320.0;
			indice_p = 2.0;
			indice_d = 1.6;
			indice_g = 110.8;

		}
		else if (maior_fusivel == 65)
		{
			indice_k = 370.0;
			indice_p = 2.0;
			indice_d = 2.34;
			indice_g = 195.8;

		}
		else if (maior_fusivel == 100)
		{
			indice_k = 1200.0;
			indice_p = 2.03;
			indice_d = 3.6;
			indice_g = 720.0;

		}
		else if (maior_fusivel == 140)
		{
			indice_k = 2000.0;
			indice_p = 2.1;
			indice_d = 8.1;
			indice_g = 2600.0;

		}
		else if (maior_fusivel == 200)
		{
			indice_k = 2040.0;
			indice_p = 2.1;
			indice_d = 21.0;
			indice_g = 9000.0;

		}
		else
		{
			printf ("Fusivel não coordena com o relé\n");
		}
	}

	for (int i1 = 0; i1 < intervalo; i1++)
	{
		/*M_fusivel             = Icc_analisados        [i1] /10.0;
		M_fusivel_neutro      = Icc_analisados_neutro [i1] /10.0;*/
		M_fusivel = Icc_analisados[i1];
		M_fusivel_neutro = Icc_analisados_neutro[i1];
		T_fusivel        [i1] = indice_d * indice_k / ( pow (M_fusivel       , indice_p) - indice_g ); // Ta escalonado por 10 devido a formula do tempo do fusivel utilizado
		T_fusivel_neutro [i1] = indice_d * indice_k / ( pow (M_fusivel_neutro, indice_p) - indice_g ); // Ta escalonado por 10 devido a formula do tempo do fusivel utilizado
	}
}

void Calculo_do_fluxo::impressao_seletividade (char nome_sistema [100])
{
	//------------------------------------------------------------------------------------------------------------------
    // Rotina de escrita dos dados no txt
    //------------------------------------------------------------------------------------------------------------------
      
	//---------------
	// Entronta os pais dos transformadores
	//---------------

	for (i = 0; i < TRAFOS_DISTRI.size (); i++)
	{
		for (j = 0; j < CHAVEPROT.size (); j++)
		{
			for (k = 0; k < CHAVEPROT[j].STRUCTFILHOSCH.size (); k++)
			{
				if (( CHAVEPROT[j].STRUCTFILHOSCH[k].Pos_struct_Filho == i ) && ( CHAVEPROT[j].STRUCTFILHOSCH[k].TiposFilhosCH == "TR" ))
				{
					TRAFOS_DISTRI[i].Struct_Pai = j;
					TRAFOS_DISTRI[i].Tipo_Pai == "CH";
				}

			}
		}
		for (j = 0; j < DISJUNTORPROT.size (); j++)
		{
			if (( DISJUNTORPROT[j].STRUCTFILHOSDJ[k].Pos_struct_Filho == i ) && ( DISJUNTORPROT[j].STRUCTFILHOSDJ[k].TiposFilhosDJ == "TR" ))
				{
					TRAFOS_DISTRI[i].Struct_Pai = j;
					TRAFOS_DISTRI[i].Tipo_Pai == "DJ";
				}
		}
	}

	//----- Verifica se os elos fusíveis estão coordenados
	for (i = 0; i < CHAVEPROT.size (); i++) // Inicializa
	{
		CHAVEPROT[i].Coordenado = "Sim";
	}

	for (i = 0; i < DISJUNTORPROT.size (); i++)
	{
		for (j = 0; j < DISJUNTORPROT[i].STRUCTFILHOSDJ.size (); j++)
		{
			if ((DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TipoChave == 0) && (DISJUNTORPROT[i].STRUCTFILHOSDJ[j].TiposFilhosDJ == "CH")) // Verifica se é um elo-fusível
			{
				if (( DISJUNTORPROT[i].I_instantaneo - 0.001 ) > CHAVEPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Icc_2f_min_protegido)
				{
					CHAVEPROT[DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho].Coordenado = "Nao";
					printf ("CH %d \n", DISJUNTORPROT[i].STRUCTFILHOSDJ[j].Pos_struct_Filho);
				}
			}
		}
	}

	for (i = 0; i < CHAVEPROT.size (); i++)
	{
		if (CHAVEPROT[i].TipoCH == 6)
		{
			for (j = 0; j < CHAVEPROT[i].STRUCTFILHOSCH.size (); j++)
			{
				if ((CHAVEPROT[i].STRUCTFILHOSCH[j].TipoChave == 0) && (CHAVEPROT[i].STRUCTFILHOSCH[j].TiposFilhosCH == "CH")) // Verifica se é um elo fusível
				{
					if (( CHAVEPROT[i].I_instantaneo - 0.001 ) > CHAVEPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Icc_2f_min_protegido)
					{
						CHAVEPROT[CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho].Coordenado = "Nao";
						printf ("CH %d \n", CHAVEPROT[i].STRUCTFILHOSCH[j].Pos_struct_Filho);
					}
				}
			}
		}
	}



	//-----


    FILE    * pFile;
    pFile   = fopen ("Resultado_Seletividade.txt","w"); 
	fprintf (pFile, "===================================================================================================================================================================\n");
    fprintf (pFile, "                                                                  Dimensionamento das Proteções                                                                    \n");
	fprintf (pFile, "===================================================================================================================================================================\n");
    fprintf (pFile, "                                                                                                          \n");
	fprintf (pFile, " Arquivo lido:\n", nome_sistema);
	fprintf (pFile, " - %s\n\n", nome_sistema);
	fprintf (pFile, " O sistema contém:\n");
	fprintf (pFile, "- %d Barras\n" , Numero_barras);
	fprintf (pFile, "- %d Linhas\n" , Numero_linhas);
	fprintf (pFile, "- %d Transformadores\n\n" , TRAFOS_DISTRI.size());
	fprintf (pFile, " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  _ _ _ _ _ _  _ _ _ _ _ _ \n");
	fprintf (pFile, "|                                                                                         |            |            |\n");
	fprintf (pFile, "|                    Proteção dos Transformadores de Distribuição                         |            |            |\n");
	fprintf (pFile, "|_ _ _ _ __ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |_ _ _ _ _ _ |_ _ _ _ _ _ |\n");
	fprintf (pFile, "|        |        |        |               |          |             |        |            |            |            |\n");
	fprintf (pFile, "|   ID   |   Ni   |   Nj   |   ID Trafo    | Potência | Elo-fusivel |  Ramo  |   IccMax   |   Icc_2ph  | Icc_1phmin |\n");
    fprintf (pFile, "| Struct |        |        |               |  [KVA]   |             |        |    [A]     |    [A]     |    [A]     |\n");
	fprintf (pFile, "|_ _ _ _ |_ _ _ _ |_ _ _ _ |_ _ _ _ _ _ _ _|_ _ _ _ _ |_ _ _ _ _ _ _|_ _ _ _ |_ _ _ _ _ _ |_ _ _ _ _ _ |_ _ _ _ _ _ |\n");

	for (i = 0 ; i < TRAFOS_DISTRI.size () ; i++)     
    {
	    fprintf (pFile, "|%8d|%8d|%8d|%15s|%10.2f|%12d%s|%8d|%12.2f|%12.2f|%12.2f|\n", i, 
			TRAFOS_DISTRI [i].Ni, TRAFOS_DISTRI [i].Nj, TRAFOS_DISTRI [i].IDtrafo.c_str(), TRAFOS_DISTRI [i].PotenciaTrafo / 1000.0, TRAFOS_DISTRI [i].ValorElo, TRAFOS_DISTRI [i].TipoElo.c_str(), TRAFOS_DISTRI [i].Ramo_ord , TRAFOS_DISTRI [i].Icc_max, TRAFOS_DISTRI [i].Icc2f_min, TRAFOS_DISTRI [i].Icc1f_min);
    }
    fprintf (pFile, "|_ _ _ _ |_ _ _ _ |_ _ _ _ |_ _ _ _ _ _ _ _|_ _ _ _ _ |_ _ _ _ _ _ _|_ _ _ _ |_ _ _ _ _ _ |_ _ _ _ _ _ |_ _ _ _ _ _ |\n");
	fprintf (pFile, "\n\n");
	fprintf (pFile, " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  _ _ _ _ _ __ _ _ _ _ _ _ _ _ _ _ _ _ \n");
	fprintf (pFile, "|                                                                                                                                                                   |\n");
	fprintf (pFile, "|                                             Chaves-Fusíveis                                                                                                       |\n");
	fprintf (pFile, "| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  _ _ _ _ _ _  _ _ _ _ _ _  _ _ _ _ _  |\n");
	fprintf (pFile, "|       |        |        |        |               |             |             |        |            |           |            |            |            |           |\n");
	fprintf (pFile, "|   ID  |   ID   |   Ni   |   Nj   |   ID Chave    | Elo-fusivel | Prefencial? |  Ramo  |   Iccmax   |Icc 1phmin |Icc 2phmin  |Coordenado? | Icc 1phas  | Icc 3phas |\n");
	fprintf (pFile, "|       | Struct |        |        |               |             |             |        |    [A]     | protegido | protegido  |            |            |           |\n");
    fprintf (pFile, "|_ _ _ _|_ _ _ _ |_ _ _ _ |_ _ _ _ |_ _ _ _ _ _ _ _|_ _ _ _ _ _ _|_ _ _ _ _ _ _|_ _ _ _ |_ _ _ _ _ _ |_ _ _ _ _ _|_ _ _ _ _ _ |_ _ _ _ _ _ |_ _ _ _ _ _ |_ _ _ _ _  |\n");

	int aux_contador_ch = 1;
	for (i = 0 ; i < CHAVEPROT.size () ; i++)     
    {
		
		if ( CHAVEPROT [i].TipoCH == 0 ) // Verifica se a chave é um elo-fusível
		{
			fprintf(pFile, "|%7d|%8d|%8d|%8d|%15s|%12d%s|%13s|%8d|%12.3f|%11.3f|%12.3f|%12s|%12.3f|%11.3f|\n", aux_contador_ch, i,
				CHAVEPROT[i].Ni, CHAVEPROT[i].Nj, CHAVEPROT[i].CodigoCH.c_str(),
				CHAVEPROT[i].ValorElo, CHAVEPROT[i].TipoElo.c_str(), Elo_Preferencial.c_str(), CHAVEPROT[i].Ramo_ord, CHAVEPROT[i].Icc_max, CHAVEPROT[i].Icc_1f_min_protegido, CHAVEPROT[i].Icc_2f_min_protegido, CHAVEPROT[i].Coordenado.c_str(), CHAVEPROT[i].Icc1f, CHAVEPROT[i].Icc3f);
			aux_contador_ch = aux_contador_ch + 1;
		}
	}
    fprintf (pFile, "|_ _ _ _|_ _ _ _ |_ _ _ _ |_ _ _ _ |_ _ _ _ _ _ _ _|_ _ _ _ _ _ _|_ _ _ _ _ _ _|_ _ _ _ |_ _ _ _ _ _ |_ _ _ _ _ _|_ _ _ _ _ _ |_ _ _ _ _ _ |_ _ _ _ _ _|_ _ _ _ _ _ |\n");
	fprintf (pFile, "\n\n");	

	fprintf (pFile, " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
	fprintf (pFile, "|                                                                                                                                                            |\n");
	fprintf (pFile, "|                                                                      Religadores                                                                           |\n");
	fprintf (pFile, "| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n");
	fprintf (pFile, "|        |        |        |                    |                    |          |          |            |              |           |             |           |\n");
	fprintf (pFile, "|   ID   |   Ni   |   Nj   |   Norma da Curva   |   Tipo de Curva    | Ipartida | Ipartida |  Dial Fase |  Dial Neutro |    I>>    |     I>>     |    RTC    |\n");
	fprintf (pFile, "| Struct |        |        |                    |                    |  Fase[A] | Neutro[A]|  Retardado |   Retardado  |  Fase[A]  |  Neutro[A]  |           |\n");
    fprintf (pFile, "|_ _ _ _ |_ _ _ _ |_ _ _ _ |_ _ _ _ _ _ _ _ _ _ |_ _ _ _ _ _ _ _ _ _ |_ _ _ _ _ |_ _ _ _ _ |_ _ _ _ _ _ |_ _ _ _ _ _ _ | _ _ _ _ _ |_ _ _ _ _ _ _|_ _ _ _ _ _|\n");
	  
	for (i = 0 ; i < CHAVEPROT.size () ; i++)     
    {
		if ( CHAVEPROT [i].TipoCH == 6 ) // Verifica se a chave é religador
		{
			fprintf (pFile, "|%8d|%8d|%8d|%20s|%20s|%10.3f|%10.3f|%12.3f|%14.3f|%11.3f|%13.3f|%9.0f/5|\n", i,
				    CHAVEPROT [i].Ni, CHAVEPROT [i].Nj,  CHAVEPROT [i].Norma_Curva_string.c_str(), CHAVEPROT [i].Tipo_Curva_string.c_str(),
					CHAVEPROT [i].Religador_Ipickup_fase, CHAVEPROT [i].Religador_Ipickup_neutro, CHAVEPROT [i].Religador_Dial_fase_retardada, CHAVEPROT [i].Religador_Dial_neutro_retardada, CHAVEPROT [i].I_instantaneo, CHAVEPROT [i].I_instantaneo_neutro, CHAVEPROT [i].RTC*5);
		}
	}
    fprintf (pFile, "|_ _ _ _ |_ _ _ _ |_ _ _ _ |_ _ _ _ _ _ _ _ _ _ |_ _ _ _ _ _ _ _ _ _ |_ _ _ _ _ |_ _ _ _ _ |_ _ _ _ _ _ |_ _ _ _ _ _ _ | _ _ _ _ _ |_ _ _ _ _ _ _|_ _ _ _ _ _|\n");
	fprintf (pFile, "\n\n");
	fprintf (pFile, " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
	fprintf (pFile, "|                                                                                                                                                       				     |\n");
	fprintf (pFile, "|                                                                           Disjuntores                                                                 				     |\n");
	fprintf (pFile, "| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ __ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n");
	fprintf (pFile, "|        |        |        |                    |                    |          |          |        |        |             |             |             |             |       |\n");
	fprintf (pFile, "|   ID   |   Ni   |   Nj   |   Norma da Curva   |   Tipo de Curva    | Ipartida | Ipartida |  Dial  |  Dial  |  Tap Fase   |     I>>     | Tap Neutro  |    I>>      |  RTC  |\n");
	fprintf (pFile, "| Struct |        |        |                    |                    |  Fase[A] | Neutro[A]|  Fase  | Neutro | Temporizado |   Fase[A]   | Temporizado | Neutro[A]   |       |\n");
    fprintf (pFile, "|_ _ _ _ |_ _ _ _ |_ _ _ _ |_ _ _ _ _ _ _ _ _ _ |_ _ _ _ _ _ _ _ _ _ |_ _ _ _ _ |_ _ _ _ _ |_ _ _ _ |_ _ _ _ |_ _ _ _ _ _ _|_ _ _ _ _ _ _|_ _ _ _ _ _ _|_ _ _ _ _ _ _|_ _ _ _|\n");
	
	for (i = 0 ; i < DISJUNTORPROT.size () ; i++)     
    {
		fprintf (pFile, "|%8d|%8d|%8d|%20s|%20s|%10.3f|%10.3f|%8.3f|%8.3f|%13.3f|%13.3f|%13.3f|%13.3f|%5.0f/5|\n", i,
				DISJUNTORPROT [i].Ni, DISJUNTORPROT [i].Nj, DISJUNTORPROT [i].Norma_Curva_string.c_str(), DISJUNTORPROT [i].Tipo_Curva_string.c_str(), 
				DISJUNTORPROT [i].Ipickup_fase,DISJUNTORPROT [i].Ipickup_neutro, DISJUNTORPROT [i].Dial_fase, DISJUNTORPROT [i].Dial_neutro,
				DISJUNTORPROT [i].Tap_Temporizado_fase, DISJUNTORPROT [i].I_instantaneo, DISJUNTORPROT [i].Tap_Temporizado_neutro, DISJUNTORPROT [i].I_instantaneo_neutro, DISJUNTORPROT [i].RTC*5);
	}
	fprintf (pFile, "|_ _ _ _ |_ _ _ _ |_ _ _ _ |_ _ _ _ _ _ _ _ _ _ |_ _ _ _ _ _ _ _ _ _ |_ _ _ _ _ |_ _ _ _ _ |_ _ _ _ |_ _ _ _ |_ _ _ _ _ _ _|_ _ _ _ _ _ _|_ _ _ _ _ _ _|_ _ _ _ _ _ _|_ _ _ _|\n");
	fprintf (pFile, "\n\n");
	fprintf (pFile, "*Os intervalos de segurança consideradoras foram:\n"                  );
	fprintf (pFile, "- Relé-Relé          %2.1f [s]\n"  , Intervalo_Coord_rele_rele        );
	fprintf (pFile, "- Relé-Fusível       %2.1f [s]\n"  , Intervalo_Coord_rele_fusivel     );
	fprintf (pFile, "- Relé-Religador     %2.1f [s]\n"  , Intervalo_Coord_rele_religador   );
	fprintf (pFile, "- Reeligador-Fusível %2.1f [s]\n\n", Intervalo_Coord_religador_fusivel);

	fprintf (pFile, "A filosofia de coordenação:\n");
	if (Coordenado_ou_seletivo == 1)
	{
		fprintf (pFile, "- Modelo Coordenado\n\n");
	}
	else
	{
		fprintf (pFile, "- Modelo Seletivo\n\n");
	}

	fprintf (pFile, "Log de coordenação:\n");

	for (i = 0 ; i < CHAVEPROT.size () ; i++)     
    {
		if ( CHAVEPROT [i].TipoCH == 6 ) // Verifica se a chave é religador
		{
			for ( j = 0; j < CHAVEPROT [i].STRUCTFILHOSCH.size (); j++)
			{
				if ( CHAVEPROT [i].STRUCTFILHOSCH [j].Coordenado == "Nao" )
				{
					if ( CHAVEPROT [i].STRUCTFILHOSCH [j].TipoChave == 0)
					{
						fprintf (pFile, "*Não houve coordenação do religador %d (protegido) com o Elo-Fusível %d de %d%s (protetor) no intervalo de %6.3f a %6.3f A\n", i, IndexStructCH [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH],
							     CHAVEPROT [i].STRUCTFILHOSCH [j].ValorElo, CHAVEPROT [i].STRUCTFILHOSCH [j].TipoEloFilhoCH.c_str (), 
								 CHAVEPROT [IndexStructCH [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH]].Icc2f_min, 
								 CHAVEPROT [IndexStructCH [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH]].Icc3f);
					}
					else if ( CHAVEPROT [i].STRUCTFILHOSCH [j].TipoChave == 6)
					{
						fprintf (pFile, "*Não houve coordenação do religador %d (protegido) com o Religador %d (protetor) no intervalo de %6.3f a %6.3f A\n", i, IndexStructCH [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH], 
								 CHAVEPROT [IndexStructCH [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH]].Icc2f_min, 
								 CHAVEPROT [IndexStructCH [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH]].Icc3f);
					}
					else if ( CHAVEPROT [i].STRUCTFILHOSCH [j].TiposFilhosCH == "DJ")
					{
						fprintf (pFile, "*Não houve coordenação do religador %d (protegido) com o Disjuntor %d (protetor) no intervalo de %6.3f a %6.3f A\n", i, IndexStructDJ [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH], 
								 DISJUNTORPROT [IndexStructDJ [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH]].Icc2f_min, 
								 DISJUNTORPROT [IndexStructDJ [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH]].Icc3f);
					}
				}

				if ( CHAVEPROT [i].STRUCTFILHOSCH [j].Coordenado_neutro == "Nao" )
				{
					if ( CHAVEPROT [i].STRUCTFILHOSCH [j].TipoChave == 0)
					{
						fprintf (pFile, "* [Neutro] Não houve coordenação do religador %d (protegido) com o Elo-Fusível %d de %d%s (protetor) no intervalo de %6.3f a %6.3f A\n", i, IndexStructCH [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH],
							     CHAVEPROT [i].STRUCTFILHOSCH [j].ValorElo, CHAVEPROT [i].STRUCTFILHOSCH [j].TipoEloFilhoCH.c_str (), 
								 CHAVEPROT [IndexStructCH [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH]].Icc2f_min, 
								 CHAVEPROT [IndexStructCH [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH]].Icc3f);
					}
					else if ( CHAVEPROT [i].STRUCTFILHOSCH [j].TipoChave == 6)
					{
						fprintf (pFile, "* [Neutro] Não houve coordenação do religador %d (protegido) com o Religador %d (protetor) no intervalo de %6.3f a %6.3f A\n", i, IndexStructCH [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH], 
								 CHAVEPROT [IndexStructCH [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH]].Icc2f_min, 
								 CHAVEPROT [IndexStructCH [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH]].Icc3f);
					}
					else if ( CHAVEPROT [i].STRUCTFILHOSCH [j].TiposFilhosCH == "DJ")
					{
						fprintf (pFile, "* [Neutro] Não houve coordenação do religador %d (protegido) com o Disjuntor %d (protetor) no intervalo de %6.3f a %6.3f A\n", i, IndexStructDJ [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH], 
								 DISJUNTORPROT [IndexStructDJ [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH]].Icc2f_min, 
								 DISJUNTORPROT [IndexStructDJ [CHAVEPROT [i].STRUCTFILHOSCH [j].Ramos_ord_FilhoCH]].Icc3f);
					}
				}
			}
			if (CHAVEPROT[i].Coordenado_dial_min == 1)
			{
				fprintf (pFile, "* O religador %d está coordenado com dial mínimo (%3.2f), desta forma não é garantido que o intervalo de coordenação seja mínimo\n", i, Dial_min);
			}
			if (CHAVEPROT[i].Coordenado_dial_min_neutro == 1)
			{
				fprintf (pFile, "* [Neutro] O religador %d está coordenado com dial mínimo (%3.2f), desta forma não é garantido que o intervalo de coordenação seja mínimo\n", i, Dial_min);
			}
		}
	}

		for (i = 0 ; i < DISJUNTORPROT.size () ; i++)     
		{
			for ( j = 0; j < DISJUNTORPROT [i].STRUCTFILHOSDJ.size (); j++)
			{
				if ( DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Coordenado == "Nao" )
				{
					if ( DISJUNTORPROT [i].STRUCTFILHOSDJ [j].TipoChave == 0)
					{
						fprintf (pFile, "*Não houve coordenação do Disjuntor %d (protegido) com o Elo-Fusível %d de %d%s (protetor) no intervalo de %6.3f a %6.3f A\n", i, IndexStructCH [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ],
									DISJUNTORPROT [i].STRUCTFILHOSDJ [j].ValorElo, DISJUNTORPROT [i].STRUCTFILHOSDJ [j].TipoEloFilhoDJ.c_str (), 
									CHAVEPROT [IndexStructCH [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ]].Icc2f_min, 
									CHAVEPROT [IndexStructCH [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ]].Icc3f);
					}
					else if ( DISJUNTORPROT [i].STRUCTFILHOSDJ [j].TipoChave == 6)
					{
						fprintf (pFile, "*Não houve coordenação do Disjuntor %d (protegido) com o Religador %d (protetor) no intervalo de %6.3f a %6.3f A\n", i, IndexStructCH [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ], 
									CHAVEPROT [IndexStructCH [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ]].Icc2f_min, 
									CHAVEPROT [IndexStructCH [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ]].Icc3f);
					}
					else if ( DISJUNTORPROT [i].STRUCTFILHOSDJ [j].TiposFilhosDJ == "DJ")
					{
						fprintf (pFile, "*Não houve coordenação do Disjuntor %d (protegido) com o Disjuntor %d (protetor) no intervalo de %6.3f a %6.3f A\n", i, IndexStructDJ [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ], 
									DISJUNTORPROT [IndexStructDJ [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ]].Icc2f_min, 
									DISJUNTORPROT [IndexStructDJ [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ]].Icc3f);
					}
				}

				if ( DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Coordenado_neutro == "Nao" )
				{
					if ( DISJUNTORPROT [i].STRUCTFILHOSDJ [j].TipoChave == 0)
					{
						fprintf (pFile, "* [Neutro] Não houve coordenação do Disjuntor %d (protegido) com o Elo-Fusível %d de %d%s (protetor) no intervalo de %6.3f a %6.3f A\n", i, IndexStructCH [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ],
									DISJUNTORPROT [i].STRUCTFILHOSDJ [j].ValorElo, DISJUNTORPROT [i].STRUCTFILHOSDJ [j].TipoEloFilhoDJ.c_str (), 
									CHAVEPROT [IndexStructCH [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ]].Icc2f_min, 
									CHAVEPROT [IndexStructCH [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ]].Icc3f);
					}
					else if ( DISJUNTORPROT [i].STRUCTFILHOSDJ [j].TipoChave == 6)
					{
						fprintf (pFile, "* [Neutro] Não houve coordenação do Disjuntor %d (protegido) com o Religador %d (protetor) no intervalo de %6.3f a %6.3f A\n", i, IndexStructCH [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ], 
									CHAVEPROT [IndexStructCH [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ]].Icc2f_min, 
									CHAVEPROT [IndexStructCH [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ]].Icc3f);
					}
					else if ( DISJUNTORPROT [i].STRUCTFILHOSDJ [j].TiposFilhosDJ == "DJ")
					{
						fprintf (pFile, "* [Neutro] Não houve coordenação do Disjuntor %d (protegido) com o Disjuntor %d (protetor) no intervalo de %6.3f a %6.3f A\n", i, IndexStructDJ [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ], 
									DISJUNTORPROT [IndexStructDJ [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ]].Icc2f_min, 
									DISJUNTORPROT [IndexStructDJ [DISJUNTORPROT [i].STRUCTFILHOSDJ [j].Ramos_ord_FilhoDJ]].Icc3f);
					}
				}
			}

			if (DISJUNTORPROT[i].Coordenado_dial_min == 1)
			{
				fprintf (pFile, "* O Disjuntor %d está coordenado com dial mínimo (%3.2f), desta forma não é garantido que o intervalo de coordenação seja mínimo\n", i, Dial_min);
			}
			if (DISJUNTORPROT[i].Coordenado_dial_min_neutro == 1)
			{
				fprintf (pFile, "* [Neutro] O Disjuntor %d está coordenado com dial mínimo (%3.2f), desta forma não é garantido que o intervalo de coordenação seja mínimo\n", i, Dial_min);
			}
		}

	fclose (pFile); // Termina a função de escrita

	//===================================================================================================
	// Rotina de procurar pais e filhos, apenas para plotagem.
	//===================================================================================================

	FilhosCH FilhosCH_temp;
	FilhosDJ FilhosDJ_temp;
	int Aux1, Aux2;

	for ( i = Numero_linhas - 1 ; i > -1 ; i--)
	{	
		if ( Tipo_Circuito [IndexRamo [i]] == "DJ" || ( Tipo_Circuito [IndexRamo [i]] == "CH" && (Tipo_CH [IndexRamo [i]] == 0 || Tipo_CH [IndexRamo [i]] == 6) || Tipo_Circuito [IndexRamo [i]] == "TR")) // Compara se o elemento é uma Chave ou Disjuntor, se for CH, verifica se a mesma tem fusível ou religador ou um elo-fusível do Trafo
		{ 
			Aux1 = Ni_renum [i]; // Pai temporário
			Aux2 = i; // Filho procurado
			
			for (j = i -1; j > -1; j --)
			{
				if (Nj_renum [j] == Aux1) // "Caso a barra analisada tenha como Filho o Pai procurado"
				{
					if (Tipo_Circuito [IndexRamo [j]] == "DJ" || ( Tipo_Circuito [IndexRamo [j]] == "CH" && (Tipo_CH [IndexRamo [j]] == 0 || Tipo_CH [IndexRamo [j]] == 6))) //  Compara se o elemento é uma Chave ou Disjuntor, se for CH, verifica se a mesma tem fusível ou religador
					{
						if (Tipo_Circuito [IndexRamo [j]] == "CH") // Caso o elemento de proteção seja uma chave fusível ou religadora
						{
							for ( k = 0; k < CHAVEPROT.size (); k++) // Encontra na estrutura o elemento desejado e o atualiza
							{
								if (CHAVEPROT [k].Nj_renum == Nj_renum [j])
								{   
									FilhosCH_temp.Ramos_ord_FilhoCH = i;
									if ( Tipo_Circuito [IndexRamo [i]] == "CH" ) // Caso o filho seja uma chave fusível
									{
										printf ("CH %d // CH %d     \n", IndexStruct [j], IndexStruct[i]);
										//FilhosCH_temp.TiposFilhosCH = "CH"; 
										//FilhosCH_temp.TipoChave    =  Tipo_CH [IndexRamo [i]]; 
									}
									else if ( Tipo_Circuito [IndexRamo [i]] == "TR")
									{
										printf ("CH %d // TR %d\n", IndexStruct [j], IndexStruct[i]);
										//FilhosCH_temp.TipoChave    =  0; 
										//FilhosCH_temp.TiposFilhosCH = "TR";
										
									}

									//CHAVEPROT [k].STRUCTFILHOSCH.push_back (FilhosCH_temp);
									//IndexStruct [j] = k; // Indice nas estruturas dos elementos de proteção que são pais
									break;
								}
							}
						}
						else // Caso o elemento de proteção seja um disjuntor
						{
							for ( k = 0; k < DISJUNTORPROT.size (); k++) // Encontra na estrutura o elemento desejado e o atualiza
							{
								if ( DISJUNTORPROT [k].Nj_renum == Nj_renum [j])
								{
									FilhosDJ_temp.Ramos_ord_FilhoDJ = i;
									
									if ( Tipo_Circuito [IndexRamo [i]] == "CH")
									{
										printf("DJ %d // CH %d\n", IndexStruct [j], IndexStruct[i]);
										//FilhosDJ_temp.TiposFilhosDJ = "CH";
										//FilhosCH_temp.TipoChave    = Tipo_CH [IndexRamo [i]];

									}
									else if ( Tipo_Circuito [IndexRamo [i]] == "TR")
									{
										printf("DJ %d // TR %d\n", IndexStruct [j], IndexStruct[i]);
										FilhosDJ_temp.TiposFilhosDJ = "TR";
									}
									else if ( Tipo_Circuito [IndexRamo [i]] == "DJ")
									{
										printf("DJ %d // DJ %d\n", IndexStruct [j], IndexStruct[i]);
										//FilhosDJ_temp.TiposFilhosDJ = "DJ";
									}
									//DISJUNTORPROT [k].STRUCTFILHOSDJ.push_back (FilhosDJ_temp);
									//IndexStruct [j] = k; // Indice nas estruturas dos elementos de proteção que são pais
									//break;
								}
							}
						}
					}
					else // Caso o ramo no qual o Filho e o Pai procurado, o valor do pai é atualizado
					{
						Aux1 = Ni_renum [j]; // Pai novo temporário
					}
				}
			}
		}
	}
}