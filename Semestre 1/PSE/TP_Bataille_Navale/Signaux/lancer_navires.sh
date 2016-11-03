if( test $# -ne 3 ) then 
    echo "Usage: $0 <fichier bateau> <fichier amiral> <nb navires>"
    exit 1
fi 

fich_bat=$1
fich_ami=$2
nb_bateaux=$3
i=0
while( test $i -lt $nb_bateaux ) do 
	for marque in A B C D E F G H I J K L M N O P Q R S T U V W X Y Z ; do 
       if( test $i -ge $nb_bateaux ) then
           exit 0
       fi
       echo "lancement $i: bateau $marque"
       ./navire $fich_bat $fich_ami $marque  &
       i=`expr $i + 1`
   done 
done 
