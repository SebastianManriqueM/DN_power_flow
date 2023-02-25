##  <CÁLCULO DO FLUXO DE POTÊNCIA EM REDES RADIAIS DE DISTRIBUIÇÃO- LOAD FLOW IN DISTRIBUTION NETWORKS V1.0. 
##  This is the main source of this software that calculates the power flow of a distribution network described using an txt input data file >
##  Copyright (C) <2017>  <Sebastián de Jesús Manrique Machado>   <UTFPR>   <e-mail:sebastiand@utfpr.edu.br>

##  This program is free software: you can redistribute it and/or modify
##    it under the terms of the GNU General Public License as published by
##    the Free Software Foundation, either version 3 of the License, or
##    (at your option) any later version.
##
##    This program is distributed in the hope that it will be useful,
##    but WITHOUT ANY WARRANTY; without even the implied warranty of
##    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##    GNU General Public License for more details.
##
##    You should have received a copy of the GNU General Public License
##    along with this program.  If not, see <http://www.gnu.org/licenses/>.
import csv
import datetime
import numpy as np

##//------------------------------------------------------------------------------------------------------------------
##// MAIN
##//------------------------------------------------------------------------------------------------------------------
def main():
    #A_Sistema_14
    #A_Sistema_EE
    sys_name = 'A_Sistema_EE.txt'
    Numero_barras, Numero_linhas, V_base, V_ref, IndexBarra, IndexRamo, Ni_renum, Nj_renum, np_Sa, np_Ca, np_Zaa = read_data(sys_name)
    #Ni_renum, Nj_renum, Barras_renum, IndexRamo, Ni_ord, Nj_ord, Barras,
    #Sa, Sb, Sc, Ca, Cb, Cc, Zaa, Zab, Zac, Zbb, Zbc, Zcc, Zan, Zbn, Zcn, Znn, Numero_barras = read_data(sys_name)  #TIRAR COMENT

    np_Ia_nodal, np_Ia_linha, np_Va_barra, np_Sa_calc, itera = power_f_1f(Numero_barras, Numero_linhas, V_base, V_ref, IndexBarra, IndexRamo, Ni_renum, Nj_renum, np_Sa, np_Ca, np_Zaa)

    #print ('correntes LINHAS:\n', np_Ia_linha); print ('correntes Nodais:\n', np_Ia_nodal); print ('Tensões Nodais:\n', np_Va_barra)
    print_PF_reults(sys_name, 0, Numero_barras, Numero_linhas, V_base, V_ref, IndexBarra, IndexRamo, Ni_renum, Nj_renum, itera, np_Ia_nodal, np_Ia_linha, np_Va_barra, np_Sa_calc, np_Sa, np_Ca)   


##//------------------------------------------------------------------------------------------------------------------
##// Rotina LER DADOS
##//------------------------------------------------------------------------------------------------------------------
def read_data(f_name):
    print('Começo leitura de dados')
    Barras=[]; Tipo_barras=[]; Sa=[]; Sb=[]; Sc=[]; Ca=[]; Cb=[]; Cc=[];
    Zaa=[]; Zbb=[]; Zcc=[]; Zab=[]; Zac=[]; Zbc=[]; Zan=[]; Zbn=[]; Zcn=[];
    Znn=[];
    Ni=[]; Nj=[]; comprimento=[]; Ramo=[]; 
    f = open(f_name,'rt')
    reader = csv.reader(f,'excel-tab')      #'excel-tab' class specifies that the documents columns are tab-separated
    i = 0
    for row in reader:
        if i == 0:
            i = i + 1
            continue
        elif i == 1:                                            #Dados Gerais
            Tipo_sistema = int(row[0]);    Numero_barras = int(row[1]);   Numero_linhas = int(row[2]);
            Uni_linhas   = int(row[4]);    Uni_Z         = int(row[5]);   Uni_demanda  = int(row[6]); 
            #V_base       = float(row[3])*1000/(3.0**0.5);
            V_base       = float(row[3])*1000;
        else:
            if i == 2 or i == 4 or i == 5 + Numero_barras or i > 5 + Numero_barras + Numero_linhas:
                i = i + 1
                continue
            
            if i == 3:                                          #Dados S/E
                S_base = float(row[1])*1000
                #S_base = float(row[1]) * 1000                  #Está en KVA
                #V_ref  = float(row[3]) * 1000 / (3.0**0.5)
                V_ref  = float(row[3]) * 1000
                I_base = S_base / V_base 
                Z_base = (V_base**2) / S_base
                fator_D = calc_fatorD(Uni_demanda)              #FATOR PARA ADEQUAÇÃO VALORES DE DEMANDA
                fator_Z = calc_fatorZ(Uni_Z, Uni_linhas)        #FATOR PARA ADEQUAÇÃO VALORES DE IMPEDÂNCIA
                print('Fat Z',fator_Z)
                print('Uni Z',Uni_Z)
                print('Fat D',fator_D)
                print('Uni D',Uni_demanda)
                
            elif i > 4 and i <= 4 + Numero_barras:              #Dados Barras
                Barras.append(int(row[0]))
                Tipo_barras.append(int(row[1]))
                Sa.append( complex(float(row[2]) , float(row[3]) ) * fator_D / S_base )
                Sb.append( complex(float(row[4]) , float(row[5]) ) * fator_D / S_base )
                Sc.append( complex(float(row[6]) , float(row[7]) ) * fator_D / S_base )
                Ca.append( complex(float(row[8]) , float(row[9]) ) * fator_D / S_base )
                Cb.append( complex(float(row[10]) , float(row[11]) ) * fator_D / S_base )
                Cc.append( complex(float(row[12]) , float(row[13]) ) * fator_D / S_base )
                #Coluna 14 indica modelo de carga... OPCIONAL
                if Tipo_barras[i-5] == 3:                            #Identificação de barra da S/E --> Verificação OK
                    BarraSub = Barras[i-5]
                
            elif i > 5 + Numero_barras and i <= 5 + Numero_barras + Numero_linhas:   
                Ni.append( int(row[1]) )
                Nj.append( int(row[2]) )
                comprimento.append( float(row[24]) )
                Ramo.append( int(i-6) ) 
                if Uni_Z == 1:  
                    Zaa.append( (complex(float(row[3]) , float(row[4])) / Z_base) ) 
                    Zbb.append( (complex(float(row[5]) , float(row[6])) / Z_base) ) 
                    Zcc.append( (complex(float(row[7]) , float(row[8])) / Z_base) )
                    Znn.append( (complex(float(row[9]) , float(row[10])) / Z_base) )
                    Zab.append( (complex(float(row[11]), float(row[12])) / Z_base) ) 
                    Zac.append( (complex(float(row[13]), float(row[14])) / Z_base) )
                    Zan.append( (complex(float(row[15]), float(row[16])) / Z_base) )
                    Zbc.append( (complex(float(row[17]), float(row[18])) / Z_base) ) 
                    Zbn.append( (complex(float(row[19]), float(row[20])) / Z_base) ) 
                    Zcn.append( (complex(float(row[21]), float(row[22])) / Z_base) )
                else:
                    Zaa.append( (complex(float(row[3]) , float(row[4])) * comprimento[i-6] * fator_Z / Z_base) ) 
                    Zbb.append( (complex(float(row[5]) , float(row[6])) * comprimento[i-6] * fator_Z / Z_base) ) 
                    Zcc.append( (complex(float(row[7]) , float(row[8])) * comprimento[i-6] * fator_Z / Z_base) )
                    Znn.append( (complex(float(row[9]) , float(row[10])) * comprimento[i-6] * fator_Z / Z_base) )
                    Zab.append( (complex(float(row[11]), float(row[12])) * comprimento[i-6] * fator_Z / Z_base) ) 
                    Zac.append( (complex(float(row[13]), float(row[14])) * comprimento[i-6] * fator_Z / Z_base) )
                    Zan.append( (complex(float(row[15]), float(row[16])) * comprimento[i-6] * fator_Z / Z_base) )
                    Zbc.append( (complex(float(row[17]), float(row[18])) * comprimento[i-6] * fator_Z / Z_base) ) 
                    Zbn.append( (complex(float(row[19]), float(row[20])) * comprimento[i-6] * fator_Z / Z_base) ) 
                    Zcn.append( (complex(float(row[21]), float(row[22])) * comprimento[i-6] * fator_Z / Z_base) )
               
        i = i + 1
    #end for
    np_Sa = np.array(Sa);   np_Sb = np.array(Sb);   np_Sc = np.array(Sc);   np_Ca = np.array(Ca);   np_Cb = np.array(Cb);   np_Cc = np.array(Cc);
    np_Zaa = np.array(Zaa); np_Zbb = np.array(Zbb); np_Zcc = np.array(Zcc); np_Znn = np.array(Znn);
    np_Zab = np.array(Zab); np_Zac = np.array(Zac); np_Zan = np.array(Zan); np_Zbc = np.array(Zbc); np_Zbn = np.array(Zbn); np_Zcn = np.array(Zcn);
    print('Vbase: ',V_base)
    print('Sbase: ',S_base)
    print('Zbase: ',Z_base)

    Ni_ord, Nj_ord, IndexRamo, IndexBarra = sort_bus(Numero_linhas, Ni, Nj, BarraSub, Numero_barras, Barras)
    
    Ni_renum, Nj_renum, Barras_renum = renum_bus(Numero_linhas, Numero_barras, Ni_ord, Nj_ord, Barras)
    
    print_NiNj(f_name, Numero_linhas, Numero_barras, Ni, Nj, Barras, IndexRamo, IndexBarra, 'ORIGINAL', 0  )
    print_NiNj(f_name, Numero_linhas, Numero_barras, Ni_ord, Nj_ord, Barras, IndexRamo, IndexBarra, 'ORDENADO', 1)
    print_NiNj(f_name, Numero_linhas, Numero_barras, Ni_renum, Nj_renum, Barras_renum, IndexRamo, IndexBarra, 'RENUMERADO', 1)
    
    #return Ni_renum, Nj_renum, Barras_renum, IndexRamo, Ni_ord, Nj_ord, Barras,
    #np_Sa, np_Sb, np_Sc, np_Ca, np_Cb, np_Cc, np_Zaa, np_Zab, np_Zac, np_Zbb, np_Zbc, np_Zcc, np_Zan, np_Zbn, np_Zcn, np_Znn, Numero_barras
    return Numero_barras, Numero_linhas, V_base, V_ref, IndexBarra, IndexRamo, Ni_renum, Nj_renum, np_Sa, np_Ca, np_Zaa

##//------------------------------------------------------------------------------------------------------------------
##// Rotina de Ordenar
##//------------------------------------------------------------------------------------------------------------------
def sort_bus(Numero_linhas, Ni, Nj, BarraSub, Numero_barras, Barras ):
    print('Começo Ordenamento de dados')
    #IndexRamo: indica posição da línea antes de ordenar
    #Index:     indica quais linhas JÁ foram ordenadas (1)
    #iNumero_linhas=int(Numero_linhas)
    Ni_ord = [0]*Numero_linhas;     Nj_ord = [0]*Numero_linhas;     IndexRamo = [0]*Numero_linhas;
    Index = [0]*Numero_linhas;      IndexBarra = [0]*Numero_barras;
    j = 0;
    for i in range(0, Numero_linhas):
        if Ni[i] == BarraSub:               #Identificar Subestação e alimentadores principais
            Ni_ord[j]    =  Ni[i]
            Nj_ord[j]    =  Nj[i]
            IndexRamo[j] = i
            Index[i]     = 1
            j = j + 1
            
        elif Nj[i] == BarraSub:
            Ni_ord[j]    =  Nj[i]
            Nj_ord[j]    =  Ni[i]
            IndexRamo[j] = i
            Index[i]     = 1
            j = j + 1
    #end for
    k = 0;
    while (j < Numero_linhas):              #Ordenar linhas por camadas hierárquicas
        for i in range(0, Numero_linhas):
            
            if ( Nj_ord[k] == Ni[i] and Index[i] == 0 ):
                Ni_ord[j]    = Nj_ord[k]
                Nj_ord[j]    = Nj[i]
                IndexRamo[j] = i
                Index[i]     = 1
                j = j + 1
                
            elif ( Nj_ord[k] == Nj[i] and Index[i] ==0 ):
                Ni_ord[j]    = Nj_ord[k]
                Nj_ord[j]    = Ni[i]        #aqui há diferença, conferir
                IndexRamo[j] = i
                Index[i]     = 1
                j = j+1
        k = k + 1

    for i in range(0, Numero_barras):       #Calcular Index barra
        if Barras[i] == BarraSub:   IndexBarra[0] = i; break;
        
    aux = 1;
    for i in range(0, Numero_linhas):
        for j in range(0, Numero_barras):
            
            if Nj_ord[i] == Barras[j]:
                IndexBarra[aux] = j
                aux             = aux + 1
                break
            
    return Ni_ord, Nj_ord, IndexRamo, IndexBarra

##//------------------------------------------------------------------------------------------------------------------
##// Rotina de Renumeração
##//------------------------------------------------------------------------------------------------------------------
def renum_bus(Numero_linhas, Numero_barras, Ni_ord, Nj_ord, Barras):
    Ni_renum = [0]*Numero_linhas;     Nj_renum = [0]*Numero_linhas;
    Barras_renum = [0]*Numero_barras;
    
    Ni_renum[0] = 0;    Nj_renum[0] = 1;        #Inicializar
    for i in range(1, Numero_linhas):           #Sistemas radiais sempre cumprem que Nj fica na ordem desde o primeiro nó filho
        Nj_renum[i] = i+1
        if Ni_ord[i] == Ni_ord[0]:
            Ni_renum[i] = 0
    
    for i in range(0, Numero_linhas):           #Monta Ni_Renum
        for j in range(1, Numero_linhas):   
            if Ni_ord[j] == Nj_ord[i]:
                Ni_renum[j] = i + 1
            
    for i in range(0, Numero_barras):           #Monta Barras_renum
        for j in range(0, Numero_linhas):
            
            if Barras[i] == Ni_ord[j]:
                Barras_renum[i] = Ni_renum[j]
                break
            elif Barras[i] == Nj_ord[j]:
                Barras_renum[i] = Nj_renum[j]
                break
                
    return Ni_renum, Nj_renum, Barras_renum

##//------------------------------------------------------------------------------------------------------------------
##// Rotina CALCULO FLUXO DE POTÊNCIA MONOFÁSICO
##//------------------------------------------------------------------------------------------------------------------
def power_f_1f(Numero_barras, Numero_linhas, V_base, V_ref, IndexBarra, IndexRamo, Ni_renum, Nj_renum, np_Sa, np_Ca, np_Zaa):
    np_Va_barra = np.array([complex(0,0)]*Numero_barras);   np_Delta_Sa = np.array([complex(0,0)]*2);   np_Ia_nodal = np.array([complex(0,0)]*Numero_barras);
    np_Ia_linha = np.array([complex(0,0)]*Numero_barras);   np_Va_barra_ant = np.array([complex(0,0)]*Numero_barras);
    tol = 0.000004
    
    for i in range(0, Numero_barras):           #Inicializar Tensões nos nós
        np_Va_barra [i] = V_base/V_ref;

    Convergiu = 0
    itera  = 0
    while(Convergiu < 1):
        np_Delta_Sa[0] = np_Va_barra[0] * np.conjugate(np_Ia_linha[0])

        for i in range(0, Numero_barras):           #-CALCULO CORRENTES DOS NÓS (CARGAS)-
            #np_Ia_nodal[i]    = np.conjugate( -( np_Sa[IndexBarra[i]] + np_Ca[IndexBarra[i]] ) / np_Va_barra[i] )
            np_Ia_nodal[i]    = np.conjugate( -( np_Sa[IndexBarra[i]] + np_Ca[IndexBarra[i]] ) / np_Va_barra[i] )
        
        np_Ia_linha = np.array([complex(0,0)]*Numero_barras);
        for i in range(Numero_barras-1, 0, -1):     #-CALCULO CORRENTES NAS LINHAS- VARREDURA INVERSA
            np_Ia_linha[i]              = np_Ia_linha[i] - np_Ia_nodal[i]
            np_Ia_linha[Ni_renum[i-1]]  = np_Ia_linha[Ni_renum[i-1]] + np_Ia_linha[i]

        np_Va_barra_ant = np_Va_barra
        print('----ITERAÇÕES-----: ',itera);    print ('Tensões Nodais:\n', np_Va_barra);   print ('I linhas:\n', np_Ia_linha);
        for i in range(0, Numero_linhas):           #-CALCULO TENSÕE NAS BARRAS- VARREDURA DIRETA
            np_Va_barra[Nj_renum[i]]    = np_Va_barra[Ni_renum[i]] - ( np_Zaa[IndexRamo[i]] * np_Ia_linha[i+1] )
            #print(str(np_Va_barra[Nj_renum[i]]) + '=' + str(np_Va_barra[Ni_renum[i]]) + '-' + str(np_Zaa[IndexRamo[i]]) + '*' + str(np_Ia_linha[i+1]))

        np_Delta_Sa[1] = np_Va_barra[0] * np.conjugate(np_Ia_linha[0])
        b_array = abs(np_Va_barra_ant - np_Va_barra)< tol
        
        if abs(np_Delta_Sa[0] - np_Delta_Sa[1]) < tol:
        #if np.sum(b_array) == len(b_array):
            Convergiu = 2
        itera     = itera + 1
        #print_itera(itera, Numero_barras, Numero_linhas, np_Va_barra, np_Ia_linha)
##        print('----ITERAÇÕES-----: ',itera);  print ('Tensões Nodais:\n', np_Va_barra);

    np_Sa_calc = np_Va_barra * np.conjugate(np_Ia_nodal)
    print('iterações realizadas: ', itera)
    return np_Ia_nodal, np_Ia_linha, np_Va_barra, np_Sa_calc, itera


##//------------------------------------------------------------------------------------------------------------------
##// Rotinas de Impressão em TXT ITERAÇÕES
##//------------------------------------------------------------------------------------------------------------------
##def print_itera(itera, Numero_barras, Numero_linhas, np_Va_barra, np_Ia_linha):
##    
##    if itera == 1:
##        f = open('0Sis'+str(Numero_barras)+"_"+"ITERA-results.txt",'w')
##        f.write("\n\tCálculo_Fluxo_de_Potência em redes de Distribuição\n\tSebastián de Jesús Manrique Machado\t2017\n\tEESC-USP\n ")
##        f.write("\n Resultados iterações "+str(itera))
##    else mode == 1:
##        f = open('0Sis'+str(Numero_barras)+"_"+"ITERA-results.txt",'a')
##        f.write("\n")
##    
##    f.write('\n\n---BARRAS---\n')
##    f.write('\nIter\tV1r []\tVi []\tInr\tInim\tSnr\tSnim\tSnrd\tSnimd\n')
##    for i in range(0, Numero_barras):
##        f.write(str(itera) + '\t' + str(round(np_Va_barra[i],3)) + '\t' + str(round(np_Ia_nodal[i],3)) + '\t' + str(round(np_Sa_calc[i],3)) + '\t' + str(round(np_Sa[IndexBarra[i]] + np_Ca[IndexBarra[i]],3)) + '\n')
##
##    f.write('\n---LINHAS---\n')
##    f.write('\n---Corrente total Subestação: ' + str(round(np_Ia_linha[0],3)) + '\n')
##    f.write('\nPos\tNi\tNj\tIlinr\tIinim\tInjr\tInji\t\n')    
##    for i in range(0, Numero_linhas):
##        f.write(str(i) + '\t' + str(Ni_renum[i]) + '\t' + str(Nj_renum[i]) + '\t' + str(round(np_Ia_linha[i+1],3)) + '\t' + str(round(np_Ia_nodal[Nj_renum[i]],3)) + '\n')

##//------------------------------------------------------------------------------------------------------------------
##// Rotinas de Impressão em TXT ORDENAMENTO E RENUMERAÇÃO
##//------------------------------------------------------------------------------------------------------------------
def print_NiNj(file_name, Numero_linhas, Numero_barras, Ni, Nj, Barras, IndexRamo, IndexBarra, texto, mode):
    print('Começo impresão de dados')
    
    if mode == 0:
        f = open(file_name+"_"+"results.txt",'w')
        f.write("\n Arquivo Analisado: "+file_name)
    elif mode == 1:
        f = open(file_name+"_"+"results.txt",'a')
        f.write("\n")
        f.write("\n\t+++*** ||-RESULTADOS "+texto+"-|| ***+++")
        f.write('\n INDEX BARRA \n')
        f.write('Pos\tIdxB\tBus\n')
        for i in range(0, Numero_barras):
            f.write( str(i) + '\t' + str(IndexBarra[i]) + '\t' + str(Barras[i]) + '\n' )
    else:
        f = open(file_name+"_"+"results.txt",'a')
        f.write("\n")
        f.write("\n\t+++*** ||-RESULTADOS "+texto+"-|| ***+++")

    f.write('Nó inicial e final '+texto)
    f.write('\npos\tidx\tNi\tNj\n')
    for i in range(0, Numero_linhas):
        f.write(str(i) + '\t' + str(IndexRamo[i]) + '\t' + str(Ni[i]) + '\t' + str(Nj[i]) + '\n')
##//------------------------------------------------------------------------------------------------------------------
##// Rotinas de Impressão em TXT RESULTADOS FLUXO DE POTÊNCIA
##//------------------------------------------------------------------------------------------------------------------
def print_PF_reults(file_name, mode, Numero_barras, Numero_linhas, V_base, V_ref, IndexBarra, IndexRamo, Ni_renum, Nj_renum, itera, np_Ia_nodal, np_Ia_linha, np_Va_barra, np_Sa_calc, np_Sa, np_Ca):
    print('Começo impresão de Resultados Fluxo')
    
    if mode == 0:
        f = open(file_name+"_"+"FPresults.txt",'w')
        f.write("\n\tCálculo_Fluxo_de_Potência em redes de Distribuição\n\tSebastián de Jesús Manrique Machado\t2017\n\tEESC-USP\n ")
        f.write("\n Arquivo Analisado: "+file_name)
        f.write("\n Iterações realizadas: "+str(itera))
    elif mode == 1:
        f = open(file_name+"_"+"FPresults.txt",'a')
        f.write("\n")
    
    f.write('\n\n---BARRAS---\n')
    f.write('\nBarra\tVr []\tVi []\tInr\tInim\tSnr\tSnim\tSnrd\tSnimd\n')
    for i in range(0, Numero_barras):
        f.write(str(i) + '\t' + str(round(np_Va_barra[i],3)) + '\t' + str(round(np_Ia_nodal[i],3)) + '\t' + str(round(np_Sa_calc[i],3)) + '\t' + str(round(np_Sa[IndexBarra[i]] + np_Ca[IndexBarra[i]],3)) + '\n')

    f.write('\n---LINHAS---\n')
    f.write('\n---Corrente total Subestação: ' + str(round(np_Ia_linha[0],3)) + '\n')
    f.write('\nPos\tNi\tNj\tIlinr\tIinim\tInjr\tInji\t\n')    
    for i in range(0, Numero_linhas):
        f.write(str(i) + '\t' + str(Ni_renum[i]) + '\t' + str(Nj_renum[i]) + '\t' + str(round(np_Ia_linha[i+1],3)) + '\t' + str(round(np_Ia_nodal[Nj_renum[i]],3)) + '\n')


        
def calc_fatorD(Uni_demanda):
    if Uni_demanda == 1:    fator_D = 1
    elif Uni_demanda == 2:  fator_D = 1000
    elif Uni_demanda == 3:  fator_D = 1000000
    return fator_D

def calc_fatorZ(Uni_Z, Uni_linhas):
    if (Uni_Z == 1 and Uni_linhas == 1):  fator_Z = 1.0;    	
    if (Uni_Z == 2 and Uni_linhas == 1):  fator_Z = 1.0;    	
    if (Uni_Z == 2 and Uni_linhas == 2):  fator_Z = 1000.0; 
    if (Uni_Z == 3 and Uni_linhas == 1):  fator_Z = 1.0e-3; 	
    if (Uni_Z == 3 and Uni_linhas == 2):  fator_Z = 1.0;    
    if (Uni_Z == 4 and Uni_linhas == 1):  fator_Z = 3.2780; 	
    if (Uni_Z == 4 and Uni_linhas == 2):  fator_Z = 3278.0; 
    if (Uni_Z == 5 and Uni_linhas == 1):  fator_Z = 6.21e-5;	
    if (Uni_Z == 5 and Uni_linhas == 2):  fator_Z = 6.21e-2;
    if (Uni_Z == 5 and Uni_linhas == 3):  fator_Z = 1.89e-4;
    return fator_Z


    

if __name__ == "__main__":
    main()
