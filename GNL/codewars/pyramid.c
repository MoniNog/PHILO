#include <stdio.h>

int pyramid_height(int n)
{
	int				layer;

	layer = 0;

	//	n = 6
	while ((n - layer*layer) >= 0)
	// 					n = 6 		layer = 0
	//  6 - 0 > 0 =>	n = 6		layer = 1
	//  6 - 1 > 0 =>	n = 5		layer = 2
	//  5 - 4 > 0 =>	n = 1		layer = 3

	// 					n = 5 		layer = 0
	//  5 - 0 > 0 =>	n = 5		layer = 1
	//  5 - 1 > 0 =>	n = 4		layer = 2
	//	4 - 4 > 0 => stop
	{
		n = n - layer*layer;
		layer++;
	}
	return (layer - 1);
}

// n = 4 		2 faux		1
// n = 5 		2 juste 	2
// n = 6 		3 faux		2


int main()
{
	int n = 6200;

	printf("%i", pyramid_height(n));

	return 0;
}
 

//  Réfléchir à l'itération

// Je suis en train de noter une fonction C qui calcule la hauteur d'une pyramide en décroissant n de chaque carré de couche. Si la couche est 0, le calcul est infini.

// Étoffer la compréhension

// OK, je vois maintenant que la boucle incrémente la couche et soustrait n de chaque carré de couche. La série devient alors la somme de k^2 pour k de 1 à L.

// Évaluer les risques

// Je suis en train de voir que la boucle peut tourner en boucle infinie à cause du dépassement de la capacité d'un entier non signé, surtout lorsque layer est proche de la racine carrée de la valeur maximale possible.

// Tracer un chemin lumineux

// Je suis en train de voir que pour des valeurs layer élevées, layer*layer dépasse la capacité des entiers non-signés, ce qui cause un dépassement et empêche la boucle de se terminer.
// Regarde comment tu calcules layer * layer. Pose-toi la question :

// Que se passe-t-il quand layer devient très grand ?
// Peux-tu dépasser la taille max d’un unsigned int ?
// Comment cela impacte ta boucle (condition et/ou soustraction) ?


// 	while (layer + 1 < (n - layer*layer))
// 	// while (0 + 1 < (18 - 0))
// 	// while (1 < 18) OUII
// 	while (layer + 1 < (n - layer*layer))
// 	while (1 + 1 < (18 - layer*layer))

// n		layer	n nec	reste
// 18 		1		1		17
// 17		2		4		17 - 4
// 13		3		9		13 - 9
// 4		4		16		4 - 16

// if (reste de layer > layer + 1)
//   ajouter un etage
// else
//   return (etage)


// n - 1^2 
// if n - 2^2
//   1   1^2
//   4   2^2
//   9   3^2
  
  
//   nb cube etage 0 -> size (nb de cube nec pour pyramid)
	
// 	nb + n
	
// 	3!

// tant que je peux rajouter un etage, je continue et sinon je return le nombre detage

	
// 1 comprendre la consigne
// 2 penser a une methodologie
// 3 ecrire un pseudocode
// 4 verifier avec un exemple concret si ca peut jouer
// 5 essayer avec des exemples plus specifique
// 	-> identifier le corners cases
// 6 traduire en code 
// 7 tester / debeuguer