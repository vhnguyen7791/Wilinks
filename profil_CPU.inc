#========================================================================
# NOM DU FICHIER  : profil_CPU.inc
#========================================================================
# Auteur          : CM
# Date  		  : 23/04/2013
# Libelle         : Include profil pour compilation SODIELEC / CPU
# Projet          : WILINK
# Indice          : BE000
#========================================================================
# Historique      :                                                      
#BE000 23/04/2013 CM
# - CREATION
#========================================================================


#Compilation net-snmp (n: d�sactiv�; y:activ�)
export make_net_snmp=n

#Support login password (n: d�sactiv�; y:activ�)
export make_login_password=y

#Support fram (n: d�sactiv�; y:activ�)
export make_fram=y

#Support simulation FRAM (pour compilation sur PC 64bits, simulation FRAM non support�e)  (n: d�sactiv�; y:activ�)
export make_simulation_FRAM=n

#Support eeprom (n: d�sactiv�; y:activ�)
export make_eeprom=y

#Compilation debug en cours developpement
#n: compilation debug d�sactive
#y: compilation debug active
export make_DEBUG_DVLPMT=y

