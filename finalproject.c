#define _CRT_SECURE_NO_WARNINGS
#define SPADE   "\x06"
#define HEART   "\x03"
#define CLUB    "\x05"
#define DIAMOND "\x04"
#define MAX 20
//Libraries
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
//Struct definitions
typedef struct card_s {
	char suit[2];
	int face;
	struct card_s* listp;
	int index;
}card;
typedef struct player_s {
	char name[MAX];
	struct card_s* hcardp;
	struct card_s* tcardp;
	int total;
	struct player_s* listp;
	int index;
}player;
//Swap function swaps the contents of a card excluding its index
void swap(card* x, card* y)
{
	card temp;
	temp.face = x->face;
	strcpy(temp.suit, x->suit);
	x->face = y->face;
	strcpy(x->suit, y->suit);
	y->face = temp.face;
	strcpy(y->suit, temp.suit);
}
//Deletecard function deletes a card from a linked list using double pointers
void deletecard(card **h, card **t, char shape[], int num) {
	card* targetp = *h; 	// pointer to node to be deleted
	card* prev = *h; 		// pointer to the head of the list
	while (targetp != NULL)
	{
		if (strcmp(targetp->suit, shape) == 0 && targetp->face == num) {
			break;
		}
		else {
			targetp = targetp->listp;
		}
	}

	if (targetp == NULL)
		return;
	else {
		if (targetp == *h) // if first node is to be deleted
			*h = targetp->listp; // update headp
		else {
			while (prev->listp != targetp)
				prev = prev->listp; // find the node before the target node

			if (targetp == *t) { // if last node is to be deleted
				*t = prev;// update the tail
				(*t)->listp = NULL;
			}
			else
				prev->listp = targetp->listp;  // skip node to be deleted
		}
		//free(targetp);
	} // else 
}
//Deleteroundfunction deletes the card at the end of a round
void deleteround(player* ptr, card* targetp, int i) {
	card** pheadp = &ptr[i].hcardp;
	card** ptailp = &ptr[i].tcardp;
	deletecard(pheadp, ptailp, targetp->suit, targetp->face);
}
//Addcard function is used to add a card to a linked list
void addcard(player* ptr, card* targetp, int i) {
	card** pheadp = &ptr[i-1].hcardp;
	card** ptailp = &ptr[i-1].tcardp;
	card** h = &ptr[i - 1].hcardp;
	card** t = &ptr[i - 1].tcardp;
	card* prev = ptr[i - 1].hcardp;
	card* temp;
	if (ptr[i].hcardp == NULL) //make headp point to the location that temp points to 
		ptr[i].hcardp = targetp;
	else {
		ptr[i].tcardp->listp = targetp;
	}
	ptr[i].tcardp = targetp; 		// updating tail	// setting next pt. of tail to null.
	temp = targetp;							 //allocate the memory for the next (new) node
	//targetp = targetp->listp;
	//if (prev->index == ptr[i - 1].hcardp->index) {
		//ptr[i-1].hcardp = ptr[i-1].hcardp->listp;
	//}
	if (targetp == *h) // if first node is to be deleted
		* h = targetp->listp; // update headp
	else {
		while (prev->listp != targetp)
			prev = prev->listp; // find the node before the target node

		if (targetp == *t) { // if last node is to be deleted
			*t = prev;// update the tail
			(*t)->listp = NULL;
		}
		else
			prev->listp = targetp->listp;  // skip node to be deleted
	}
	ptr[i].tcardp->listp = NULL;
	deletecard(pheadp, ptailp, temp->suit, temp->face);
}
//Addcardtop1 is used to add cards specifically to player 1 linked list
void addcardtop1(player* ptr, card* targetp) {
	card** pheadp = &ptr[3].hcardp;
	card** ptailp = &ptr[3].tcardp;
	card** h = &ptr[3].hcardp;
	card** t = &ptr[3].tcardp;
	card* prev = ptr[3].hcardp;
	card* temp;
	if (ptr[0].hcardp == NULL) //make headp point to the location that temp points to 
		ptr[0].hcardp = targetp;
	else {
		ptr[0].tcardp->listp = targetp;
	}
	ptr[0].tcardp = targetp; 		// updating tail	// setting next pt. of tail to null.
	temp = targetp;							 //allocate the memory for the next (new) node
	//targetp = targetp->listp;
	//if (prev->index == ptr[3].hcardp->index) {
		//ptr[3].hcardp = ptr[3].hcardp->listp;
	//}
	if (targetp == *h) // if first node is to be deleted
		* h = targetp->listp; // update headp
	else {
		while (prev->listp != targetp)
			prev = prev->listp; // find the node before the target node

		if (targetp == *t) { // if last node is to be deleted
			*t = prev;// update the tail
			(*t)->listp = NULL;
		}
		else
			prev->listp = targetp->listp;  // skip node to be deleted
	}
	ptr[0].tcardp->listp = NULL;
	deletecard(pheadp, ptailp, temp->suit, temp->face);
}
//fullswap function swaps the contents of a card including its index
void fullswap(card* pt1, card* pt2) {
	card* temp;
	temp = (card*)malloc(sizeof(card));
	strcpy(temp->suit, pt1->suit);
	temp->face = pt1->face;
	temp->index = pt1->index;

	strcpy(pt1->suit, pt2->suit);
	pt1->face = pt2->face;
	pt1->index = pt2->index;

	strcpy(pt2->suit, temp->suit);
	pt2->face = temp->face;
	pt2->index = temp->index;
}
//Selection function is used to sort cards in a linked list according to index
void selection(card* pt) {
	card* temp1, *temp2;
	card* midtemp, *midtemp2;
	int i, j = 0, min;
	midtemp2 = pt;
	while (midtemp2 != NULL) {
		midtemp2 = midtemp2->listp;
		j++;
	}
	temp1 = pt;
	for (i = 1; i < j; i++) {
		while (temp1 != NULL) {
			temp2 = NULL;
			midtemp = temp1->listp;
			min = temp1->index;
			while (midtemp != NULL) {
				if (midtemp->index < min) {
					min = midtemp->index;
					temp2 = midtemp;
				}
				midtemp = midtemp->listp;
			}
			if (temp2 != NULL) {
				//if (temp1->index != temp2->index) {
					fullswap(temp1, temp2);
				//}
			}
			temp1 = temp1->listp;
		}
	}
}
//Selection 2 function is used to sorts cards in a linked list according to their suit then their faces
void selection2(card* pt) {
	card* temp1, * temp2;
	card* midtemp, * midtemp2;
	char **temp = malloc(sizeof(char) * 4);;
	int arr[4];
	int spa = 0, hea = 0, clu = 0, dia = 0;
	temp[0] = (char*)malloc(strlen(SPADE));
	temp[1] = (char*)malloc(strlen(SPADE));
	temp[2] = (char*)malloc(strlen(SPADE));
	temp[3] = (char*)malloc(strlen(SPADE));
	strcpy(temp[0], SPADE);
	strcpy(temp[1], HEART);
	strcpy(temp[2], CLUB);
	strcpy(temp[3], DIAMOND);
	int i, j = 0, min, k, l;
	midtemp2 = pt;
	while (midtemp2 != NULL) {
		if (strcmp(midtemp2->suit, SPADE) == 0) {
			spa++;
		}
		if (strcmp(midtemp2->suit, HEART) == 0) {
			hea++;
		}
		if (strcmp(midtemp2->suit, CLUB) == 0) {
			clu++;
		}
		if (strcmp(midtemp2->suit, DIAMOND) == 0) {
			dia++;
		}
		midtemp2 = midtemp2->listp;
		j++;
	}
	arr[0] = spa;
	arr[1] = hea;
	arr[2] = clu;
	arr[3] = dia;
	temp1 = pt;
	for (k = 0; k < 4; k++) {
		l = 0;
		while (l < arr[k]) {
			if (temp1 == NULL) { break; }
			temp2 = NULL;
			midtemp = temp1->listp;
			while (midtemp != NULL) {
				if (strcmp(midtemp->suit, temp[k]) == 0) {
						temp2 = midtemp;
				}
				midtemp = midtemp->listp;
			}
			if (temp2 != NULL) {
				//if (temp1->index != temp2->index) {
				fullswap(temp1, temp2);
				//}
			}
			temp1 = temp1->listp;
			l++;
		}
	}
	//for (i = 1; i < j; i++) {
		//while (temp1 != NULL) {
	temp1 = pt;
			for (k = 0; k < 4; k++) {
				l = 0;
				while (l < arr[k]) {
					if (temp1 == NULL) { break; }
					temp2 = NULL;
					midtemp = temp1->listp;
					min = temp1->face;
					while (midtemp != NULL) {
						if (strcmp(midtemp->suit, temp[k]) == 0) {
							if (midtemp->face < min) {
								min = midtemp->face;
								temp2 = midtemp;
							}
						}
						midtemp = midtemp->listp;
					}
					if (temp2 != NULL) {
						//if (temp1->index != temp2->index) {
						fullswap(temp1, temp2);
						//}
					}
					temp1 = temp1->listp;
					l++;
				}
			}
		//}
	//}
}
//Reassignindex function is used to reassign index to a linked list after sorting or a card has been added
void reassignindex(card* pt) {
	int i = 1;
	while (pt != NULL) {
		pt->index = i;
		i++;
		pt = pt->listp;
	}
}
//Shuffle function is used to shuffle a deck of 52 cards
void shuffle(card* pt2) {
	card *head;
	head = pt2;
	srand((int)time(0));
	int times = 0;
	int n1, n2;
	card *node1 = NULL, *node2 = NULL;
	while (times < 100) {
		pt2 = head;
		n1 = rand() % 53;
		n2 = rand() % 53;
		if (n1 != n2) {
			while (pt2 != NULL) {
				if (pt2->index == n1) {
					node1 = pt2;
					pt2 = pt2->listp;
				}
				if (pt2 != NULL) {
					if (pt2->index == n2) {
						node2 = pt2;
						pt2 = pt2->listp;
					}
				}
				if (pt2 != NULL) {
					pt2 = pt2->listp;
				}
			}
		}
		if (node1 != NULL && node2 != NULL) {
			fullswap(node1, node2);
		}
		times++;
	}
}
//printcard function is used to print a singular card
void printcard(card* pt) {
	if (pt->face == 1) {
		printf("A%s ", pt->suit);
	}
	else if (pt->face == 11) {
		printf("J%s ", pt->suit);
	}
	else if (pt->face == 12) {
		printf("Q%s ", pt->suit);
	}
	else if (pt->face == 13) {
		printf("K%s ", pt->suit);
	}
	else {
		printf("%d%s ", pt->face, pt->suit);
	}
	printf("\n");
}
//printcard function is used to print all cards in a linked list
void printdeck(card *pt) {
	int i, j;
	while (pt != NULL) {
		for (i = 0; i < 4; i++) {
			for (j = 1; j <= 13; j++) {
				if (pt != NULL) {
					if (pt->face == 1) {
						printf("A%s ", pt->suit);
					}
					else if (pt->face == 11) {
						printf("J%s ", pt->suit);
					}
					else if (pt->face == 12) {
						printf("Q%s ", pt->suit);
					}
					else if (pt->face == 13) {
						printf("K%s ", pt->suit);
					}
					else {
						printf("%d%s ", pt->face, pt->suit); 
					}
					pt = pt->listp;
				}
			}
			if (pt != NULL) {
				printf("\n");
			}
		}
		printf("\n");
	}
}
//Choosecard funtion is used to choose a card based on chosen index
card* choosecard(player* ptr, card* pt, int fac, char suit[5], int playerpos) {
	pt = ptr[playerpos].hcardp;
	while (pt != NULL) {
		if (pt->face == fac) {
			if (strcmp(pt->suit, suit) == 0) {
				break;
			}
		}
		pt = pt->listp;
	}
	return pt;
}
//Check function is used to check total score of the 4 cards played in a round and returns the winner of the round and the total points acquired using reference
int check(card* p0, card* p1, card* p2, card* p3, char targetsuit[5], int *total) {
	int max = 0;
	if (strcmp(p0->suit, targetsuit) == 0) {
		if (p0->face > max) {
			max = p0->face;
		}
	}
	if (strcmp(p0->suit, HEART) == 0) {
		*total = *total + 1;
	}
	if (strcmp(p0->suit, SPADE) == 0) {
		if (p0->face == 12) {
			*total = *total + 13;
		}
	}


	if (strcmp(p1->suit, targetsuit) == 0) {
		if (p1->face > max) {
			max = p1->face;
		}
	}
	if (strcmp(p1->suit, HEART) == 0) {
		*total = *total + 1;
	}
	if (strcmp(p1->suit, SPADE) == 0) {
		if (p1->face == 12) {
			*total = *total + 13;
		}
	}


	if (strcmp(p2->suit, targetsuit) == 0) {
		if (p2->face > max) {
			max = p2->face;
		}
	}
	if (strcmp(p2->suit, HEART) == 0) {
		*total = *total + 1;
	}
	if (strcmp(p2->suit, SPADE) == 0) {
		if (p2->face == 12) {
			*total = *total + 13;
		}
	}

	if (strcmp(p3->suit, targetsuit) == 0) {
		if (p3->face > max) {
			max = p3->face;
		}
	}
	if (strcmp(p3->suit, HEART) == 0) {
		*total = *total + 1;
	}
	if (strcmp(p3->suit, SPADE) == 0) {
		if (p3->face == 12) {
			*total = *total + 13;
		}
	}
	if (strcmp(p0->suit, targetsuit) == 0) {
		if (p0->face == 1) {
			max = p0->face;
		}
	}
	if (strcmp(p1->suit, targetsuit) == 0) {
		if (p1->face == 1) {
			max = p1->face;
		}
	}
	if (strcmp(p2->suit, targetsuit) == 0) {
		if (p2->face == 1) {
			max = p2->face;
		}
	}
	if (strcmp(p3->suit, targetsuit) == 0) {
		if (p3->face == 1) {
			max = p3->face;
		}
	}
	if (p0->face == max) {
		return 0;
	}
	else if (p1->face == max) {
		return 1;
	}
	else if (p2->face == max) {
		return 2;
	}
	else if (p3->face == max) {
		return 3;
	}
}
//roundfunction executes all the rouns in a games and has the order ever game should be played. It returns the index of the player that won the round
int roundfunction(player* ptr, int targetindex, int *heartbreak, int *first, int turn, int* pscore) {
	player* playerp = (player*)malloc(sizeof(player) * 4);
	playerp[0] = ptr[0];
	playerp[1] = ptr[1];
	playerp[2] = ptr[2];
	playerp[3] = ptr[3];
	char c;
	card* pcard = (card*)malloc(sizeof(card) * 4);
	int chosenindex;
	card* p0card = (card*)malloc(sizeof(card));
	card* p1card = (card*)malloc(sizeof(card));
	card* p2card = (card*)malloc(sizeof(card));
	card* p3card = (card*)malloc(sizeof(card));
	card* targetc;
	int havecard;
	int maxface;
	int minface;
	int chosenface;
	char suit[5];
	char targetsuit[5];
	int total = 0;
	int winner;
	int heartcard;
	//ptr = (player*)malloc(sizeof(player) * 4);
	printf("\n");
	if (targetindex == 0) {
		if (*first == 0) {
			printf("Turn %d, %s will lead \n", turn, playerp[0].name);
			while (1) {
				printf("Enter card number between 1-%d where 1 is the leftmost card: ", playerp[0].total);
				scanf("%d", &chosenindex);
				printf("\n");
				if (chosenindex <= 0) {
					printf("card number must be greater than 0\n");
				}
				if (chosenindex > playerp[0].total) {
					printf("card number must be less than %d\n", playerp[0].total);
				}
				heartcard = 1;
				targetc = playerp[0].hcardp;
				chosenface = 20;
				while (targetc != NULL) {
					if (strcmp(targetc->suit, DIAMOND) == 0 || strcmp(targetc->suit, CLUB) == 0 || strcmp(targetc->suit, SPADE) == 0) {
						heartcard = 0;
					}
					if (targetc->index == chosenindex) {
						chosenface = targetc->face;
						strcpy(suit, targetc->suit);
						break;
					}
					targetc = targetc->listp;
				}
				if (*heartbreak == 0) {
					if (heartcard == 0) {
						if (strcmp(suit, HEART) == 0) {
							printf("You cannot lead with heart if heart isn't broken or you have cards of another suit\n");
						}
						else if (strcmp(suit, HEART) != 0 && chosenindex > 0 && chosenindex <= playerp[0].total) {
							break;
						}
					}
					else if (heartcard == 1 && chosenindex > 0 && chosenindex <= playerp[0].total) {
						break;
					}
				}
				else if(*heartbreak == 1 && chosenindex > 0 && chosenindex <= playerp[0].total) {
					break;
				}
			}
			while (targetc != NULL) {
				if (targetc->index == chosenindex) {
					chosenface = targetc->face;
					strcpy(suit, targetc->suit);
					break;
				}
				targetc = targetc->listp;
			}
			//use index to return face and suit and use for choosecard func
			p0card = choosecard(playerp, p0card, chosenface, suit, 0);
		}
		else if(*first == 1){
			targetc = playerp[0].hcardp;
			while (targetc != NULL) {
				if (targetc->face == 2 && strcmp(targetc->suit, CLUB) == 0) {
					p0card = targetc;
				}
				targetc = targetc->listp;
			}
			*first = 0;
			printf("Turn %d, %s will lead with ", turn, playerp[0].name);
			printcard(p0card);
		}
		printf("Turn %d, %s plays: ", turn, playerp[0].name);
		printcard(p0card);

		strcpy(targetsuit, p0card->suit);

		targetc = playerp[1].hcardp;
		havecard = 0;
		maxface = 0;
		minface = 14;
		while (targetc != NULL) {
			if (strcmp(targetc->suit, targetsuit) == 0) {
				havecard = 1;
				break;
			}
			else { targetc = targetc->listp; }
		}
		targetc = playerp[1].hcardp;
		if (*heartbreak == 0) {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 1) {
						maxface = 1;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face > maxface) {
						maxface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 1) {
							maxface = 1;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face > maxface) {
							maxface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p1card = choosecard(playerp, p1card, maxface, suit, 1);
		}
		else {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 2) {
						minface = 2;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face < minface) {
						minface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 2) {
							minface = 2;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face < minface) {
							minface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p1card = choosecard(playerp, p1card, minface, suit, 1);
		}
		printf("Turn %d, %s plays: ", turn, playerp[1].name);
		printcard(p1card);

		targetc = playerp[2].hcardp;
		havecard = 0;
		maxface = 0;
		minface = 14;
		while (targetc != NULL) {
			if (strcmp(targetc->suit, targetsuit) == 0) {
				havecard = 1;
				break;
			}
			else { targetc = targetc->listp; }
		}
		targetc = playerp[2].hcardp;
		if (*heartbreak == 0) {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 1) {
						maxface = 1;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face > maxface) {
						maxface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 1) {
							maxface = 1;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face > maxface) {
							maxface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p2card = choosecard(playerp, p2card, maxface, suit, 2);
		}
		else {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 2) {
						minface = 2;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face < minface) {
						minface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 2) {
							minface = 2;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->index < minface) {
							minface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p2card = choosecard(playerp, p2card, minface, suit, 2);
		}
		printf("Turn %d, %s plays: ", turn, playerp[2].name);
		printcard(p2card);

		targetc = playerp[3].hcardp;
		havecard = 0;
		maxface = 0;
		minface = 14;
		while (targetc != NULL) {
			if (strcmp(targetc->suit, targetsuit) == 0) {
				havecard = 1;
				break;
			}
			else { targetc = targetc->listp; }
		}
		targetc = playerp[3].hcardp;
		if (*heartbreak == 0) {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 1) {
						maxface = 1;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face > maxface) {
						maxface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 1) {
							maxface = 1;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face > maxface) {
							maxface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p3card = choosecard(playerp, p3card, maxface, suit, 3);
		}
		else {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 2) {
						minface = 2;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face < minface) {
						minface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 2) {
							minface = 2;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face < minface) {
							minface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p3card = choosecard(playerp, p3card, minface, suit, 3);
		}
		printf("Turn %d, %s plays: ", turn, playerp[3].name);
		printcard(p3card);

		printf("\n");
		printf("%s card is ", playerp[0].name);
		printcard(p0card);
		printf("%s card is ", playerp[1].name);
		printcard(p1card);
		printf("%s card is ", playerp[2].name);
		printcard(p2card);
		printf("%s card is ", playerp[3].name);
		printcard(p3card);
		printf("\n");
		winner = check(p0card, p1card, p2card, p3card, targetsuit, &total);
		pscore[winner] = pscore[winner] + total;
		printf("\n");
		printf("Turn %d: %s, %s, %s, %s have %d %d %d %d points\n", turn, playerp[0].name, playerp[1].name, playerp[2].name, playerp[3].name, pscore[0], pscore[1], pscore[2], pscore[3]);
		deletecard(&ptr[0].hcardp, &ptr[0].tcardp, p0card->suit, p0card->face);
		reassignindex(playerp[0].hcardp);
		deletecard(&ptr[1].hcardp, &ptr[1].tcardp, p1card->suit, p1card->face);
		reassignindex(playerp[1].hcardp);
		deletecard(&ptr[2].hcardp, &ptr[2].tcardp, p2card->suit, p2card->face);
		reassignindex(playerp[2].hcardp);
		deletecard(&ptr[3].hcardp, &ptr[3].tcardp, p3card->suit, p3card->face);
		reassignindex(playerp[3].hcardp);
		if (pscore[0] != 0 && pscore[0] != 13) {
			*heartbreak = 1;
		}
		if (pscore[1] != 0 && pscore[1] != 13) {
			*heartbreak = 1;
		}
		if (pscore[2] != 0 && pscore[2] != 13) {
			*heartbreak = 1;
		}
		if (pscore[3] != 0 && pscore[3] != 13) {
			*heartbreak = 1;
		}
		printf("***---***Hit any key to continue***---***");
		scanf(" %c", &c);
		printf("\n");
		printf("Hand after turn %d\n", turn);
		return winner;
	}
	if (targetindex == 1) {
		if (*first == 0) {
			targetc = playerp[1].hcardp;
			havecard = 0;
			maxface = 0;
			minface = 14;
			heartcard = 1;
			while (targetc != NULL) {
				if (strcmp(targetc->suit, DIAMOND) == 0 || strcmp(targetc->suit, CLUB) == 0 || strcmp(targetc->suit, SPADE) == 0) {
					heartcard = 0;
				}
				if (strcmp(targetc->suit, targetsuit) == 0) {
					havecard = 1;
					break;
				}
				else { targetc = targetc->listp; }
			}
			targetc = playerp[1].hcardp;
			if (*heartbreak == 0) {
				if (havecard == 0) {
					while (targetc != NULL) {
						if(heartcard == 1){
							if (targetc->face == 1) {
								maxface = 1;
								strcpy(suit, targetc->suit);
								break;
							}
						}
						else if (heartcard == 0) {
							if (targetc->face == 1 && strcmp(targetc->suit, HEART) != 0) {
								maxface = 1;
								strcpy(suit, targetc->suit);
								break;
							}
						}
						if (heartcard == 1) {
							if (targetc->face > maxface) {
								maxface = targetc->face;
								strcpy(suit, targetc->suit);
							}
						}
						else if (heartcard == 0) {
							if (targetc->face > maxface && strcmp(targetc->suit, HEART) != 0) {
								maxface = targetc->face;
								strcpy(suit, targetc->suit);
							}
						}
						targetc = targetc->listp;
					}
				}
				if (havecard == 1) {
					while (targetc != NULL) {
						if (strcmp(targetc->suit, targetsuit) == 0) {
							if (targetc->face == 1) {
								maxface = 1;
								strcpy(suit, targetc->suit);
								break;
							}
							if (targetc->face > maxface) {
								maxface = targetc->face;
								strcpy(suit, targetc->suit);
							}
						}
						targetc = targetc->listp;
					}
				}
				p1card = choosecard(playerp, p1card, maxface, suit, 1);
			}
			else {
				if (havecard == 0) {
					while (targetc != NULL) {
						if (targetc->face == 2) {
							minface = 2;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face < minface) {
							minface = targetc->face;
							strcpy(suit, targetc->suit);
						}
						targetc = targetc->listp;
					}
				}
				if (havecard == 1) {
					while (targetc != NULL) {
						if (strcmp(targetc->suit, targetsuit) == 0) {
							if (targetc->face == 2) {
								minface = 2;
								strcpy(suit, targetc->suit);
								break;
							}
							if (targetc->face < minface) {
								minface = targetc->face;
								strcpy(suit, targetc->suit);
							}
						}
						targetc = targetc->listp;
					}
				}
				p1card = choosecard(playerp, p1card, minface, suit, 1);
			}
			printf("Turn %d, %s will lead with: ", turn, playerp[1].name);
			printcard(p1card);
		}
		else if (*first == 1) {
			targetc = playerp[1].hcardp;
			while (targetc != NULL) {
				if (targetc->face == 2 && strcmp(targetc->suit, CLUB) == 0) {
					p1card = targetc;
				}
				targetc = targetc->listp;
			}
			*first = 0;
			printf("Turn %d, %s will lead with ", turn, playerp[1].name);
			printcard(p1card);
		}
		printf("Turn %d, %s plays: ", turn, playerp[1].name);
		printcard(p1card);

		strcpy(targetsuit, p1card->suit);

		targetc = playerp[2].hcardp;
		havecard = 0;
		maxface = 0;
		minface = 14;
		while (targetc != NULL) {
			if (strcmp(targetc->suit, targetsuit) == 0) {
				havecard = 1;
				break;
			}
			else { targetc = targetc->listp; }
		}
		targetc = playerp[2].hcardp;
		if (*heartbreak == 0) {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 1) {
						maxface = 1;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face > maxface) {
						maxface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 1) {
							maxface = 1;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face > maxface) {
							maxface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p2card = choosecard(playerp, p2card, maxface, suit, 2);
		}
		else {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 2) {
						minface = 2;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face < minface) {
						minface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 2) {
							minface = 2;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->index < minface) {
							minface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p2card = choosecard(playerp, p2card, minface, suit, 2);
		}
		printf("Turn %d, %s plays: ", turn, playerp[2].name);
		printcard(p2card);

		targetc = playerp[3].hcardp;
		havecard = 0;
		maxface = 0;
		minface = 14;
		while (targetc != NULL) {
			if (strcmp(targetc->suit, targetsuit) == 0) {
				havecard = 1;
				break;
			}
			else { targetc = targetc->listp; }
		}
		targetc = playerp[3].hcardp;
		if (*heartbreak == 0) {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 1) {
						maxface = 1;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face > maxface) {
						maxface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 1) {
							maxface = 1;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face > maxface) {
							maxface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p3card = choosecard(playerp, p3card, maxface, suit, 3);
		}
		else {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 2) {
						minface = 2;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face < minface) {
						minface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 2) {
							minface = 2;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face < minface) {
							minface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p3card = choosecard(playerp, p3card, minface, suit, 3);
		}
		printf("Turn %d, %s plays: ", turn, playerp[3].name);
		printcard(p3card);


		while (1) {
			printf("Enter card number between 1-%d where 1 is the leftmost card: ", playerp[0].total);
			scanf("%d", &chosenindex);
			printf("\n");
			havecard = 0;
			targetc = playerp[0].hcardp;
			while (targetc != NULL) {
				if (strcmp(targetc->suit, targetsuit) == 0) {
					havecard = 1;
					break;
				}
				else { targetc = targetc->listp; }
			}
			if (chosenindex <= 0) {
				printf("card number must be greater than 0\n");
			}
			else if (chosenindex > playerp[0].total) {
				printf("card number must be less than %d\n", playerp[0].total);
			}
			else if (havecard == 1) {
				targetc = playerp[0].hcardp;
				while (targetc != NULL) {
					if (targetc->index == chosenindex) {
						chosenface = targetc->face;
						strcpy(suit, targetc->suit);
						break;
					}
					targetc = targetc->listp;
				}
				if (strcmp(suit, targetsuit) != 0) {
					printf("card must have same suit as lead card\n");
				}
				else { break; }
			}
			else {
				break;
			}
		}
		if (havecard == 0) {
			targetc = playerp[0].hcardp;
			while (targetc != NULL) {
				if (targetc->index == chosenindex) {
					chosenface = targetc->face;
					strcpy(suit, targetc->suit);
					break;
				}
				targetc = targetc->listp;
			}
		}
		//use index to return face and suit and use for choosecard func
		p0card = choosecard(playerp, p0card, chosenface, suit, 0);
		printf("Turn %d, %s plays: ", turn, playerp[0].name);
		printcard(p0card);

		printf("\n");
		printf("%s card is ", playerp[0].name);
		printcard(p0card);
		printf("%s card is ", playerp[1].name);
		printcard(p1card);
		printf("%s card is ", playerp[2].name);
		printcard(p2card);
		printf("%s card is ", playerp[3].name);
		printcard(p3card);
		printf("\n");
		winner = check(p0card, p1card, p2card, p3card, targetsuit, &total);
		pscore[winner] = pscore[winner] + total;
		printf("\n");
		printf("Turn %d: %s, %s, %s, %s have %d %d %d %d points\n", turn, playerp[0].name, playerp[1].name, playerp[2].name, playerp[3].name, pscore[0], pscore[1], pscore[2], pscore[3]);
		deletecard(&ptr[0].hcardp, &ptr[0].tcardp, p0card->suit, p0card->face);
		reassignindex(playerp[0].hcardp);
		deletecard(&ptr[1].hcardp, &ptr[1].tcardp, p1card->suit, p1card->face);
		reassignindex(playerp[1].hcardp);
		deletecard(&ptr[2].hcardp, &ptr[2].tcardp, p2card->suit, p2card->face);
		reassignindex(playerp[2].hcardp);
		deletecard(&ptr[3].hcardp, &ptr[3].tcardp, p3card->suit, p3card->face);
		reassignindex(playerp[3].hcardp);
		if (pscore[0] != 0 && pscore[0] != 13) {
			*heartbreak = 1;
		}
		if (pscore[1] != 0 && pscore[1] != 13) {
			*heartbreak = 1;
		}
		if (pscore[2] != 0 && pscore[2] != 13) {
			*heartbreak = 1;
		}
		if (pscore[3] != 0 && pscore[3] != 13) {
			*heartbreak = 1;
		}

		printf("***---***Hit any key to continue***---***");
		scanf(" %c", &c);
		printf("\n");
		printf("Hand after turn %d\n", turn);
		return winner;
	}
	if (targetindex == 2) {
		if (*first == 0) {
			targetc = playerp[2].hcardp;
			havecard = 0;
			maxface = 0;
			minface = 14;
			heartcard = 1;
			while (targetc != NULL) {
				if (strcmp(targetc->suit, DIAMOND) == 0 || strcmp(targetc->suit, CLUB) == 0 || strcmp(targetc->suit, SPADE) == 0) {
					heartcard = 0;
				}
				if (strcmp(targetc->suit, targetsuit) == 0) {
					havecard = 1;
					break;
				}
				else { targetc = targetc->listp; }
			}
			targetc = playerp[2].hcardp;
			if (*heartbreak == 0) {
				if (havecard == 0) {
					while (targetc != NULL) {
						if (heartcard == 1) {
							if (targetc->face == 1) {
								maxface = 1;
								strcpy(suit, targetc->suit);
								break;
							}
						}
						else if (heartcard == 0) {
							if (targetc->face == 1 && strcmp(targetc->suit, HEART) != 0) {
								maxface = 1;
								strcpy(suit, targetc->suit);
								break;
							}
						}
						if (heartcard == 1) {
							if (targetc->face > maxface) {
								maxface = targetc->face;
								strcpy(suit, targetc->suit);
							}
						}
						else if (heartcard == 0) {
							if (targetc->face > maxface && strcmp(targetc->suit, HEART) != 0) {
								maxface = targetc->face;
								strcpy(suit, targetc->suit);
							}
						}
						targetc = targetc->listp;
					}
				}
				if (havecard == 1) {
					while (targetc != NULL) {
						if (strcmp(targetc->suit, targetsuit) == 0) {
							if (targetc->face == 1) {
								maxface = 1;
								strcpy(suit, targetc->suit);
								break;
							}
							if (targetc->face > maxface) {
								maxface = targetc->face;
								strcpy(suit, targetc->suit);
							}
						}
						targetc = targetc->listp;
					}
				}
				p2card = choosecard(playerp, p2card, maxface, suit, 2);
			}
			else {
				if (havecard == 0) {
					while (targetc != NULL) {
						if (targetc->face == 2) {
							minface = 2;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face < minface) {
							minface = targetc->face;
							strcpy(suit, targetc->suit);
						}
						targetc = targetc->listp;
					}
				}
				if (havecard == 1) {
					while (targetc != NULL) {
						if (strcmp(targetc->suit, targetsuit) == 0) {
							if (targetc->face == 2) {
								minface = 2;
								strcpy(suit, targetc->suit);
								break;
							}
							if (targetc->index < minface) {
								minface = targetc->face;
								strcpy(suit, targetc->suit);
							}
						}
						targetc = targetc->listp;
					}
				}
				p2card = choosecard(playerp, p2card, minface, suit, 2);
			}
			printf("Turn %d, %s will lead with: ", turn, playerp[2].name);
			printcard(p2card);
		}
		else if (*first == 1) {
		targetc = playerp[2].hcardp;
		while (targetc != NULL) {
			if (targetc->face == 2 && strcmp(targetc->suit, CLUB) == 0) {
				p2card = targetc;
			}
			targetc = targetc->listp;
		}
			*first = 0;
			printf("Turn %d, %s will lead with ", turn, playerp[2].name);
			printcard(p2card);
		}
		printf("Turn %d, %s plays: ", turn, playerp[2].name);
		printcard(p2card);

		strcpy(targetsuit, p2card->suit);


		targetc = playerp[3].hcardp;
		havecard = 0;
		maxface = 0;
		minface = 14;
		while (targetc != NULL) {
			if (strcmp(targetc->suit, targetsuit) == 0) {
				havecard = 1;
				break;
			}
			else { targetc = targetc->listp; }
		}
		targetc = playerp[3].hcardp;
		if (*heartbreak == 0) {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 1) {
						maxface = 1;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face > maxface) {
						maxface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 1) {
							maxface = 1;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face > maxface) {
							maxface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p3card = choosecard(playerp, p3card, maxface, suit, 3);
		}
		else {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 2) {
						minface = 2;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face < minface) {
						minface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 2) {
							minface = 2;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face < minface) {
							minface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p3card = choosecard(playerp, p3card, minface, suit, 3);
		}
		printf("Turn %d, %s plays: ", turn, playerp[3].name);
		printcard(p3card);

		while (1) {
			printf("Enter card number between 1-%d where 1 is the leftmost card: ", playerp[0].total);
			scanf("%d", &chosenindex);
			printf("\n");
			havecard = 0;
			targetc = playerp[0].hcardp;
			while (targetc != NULL) {
				if (strcmp(targetc->suit, targetsuit) == 0) {
					havecard = 1;
					break;
				}
				else { targetc = targetc->listp; }
			}
			if (chosenindex <= 0) {
				printf("card number must be greater than 0\n");
			}
			else if (chosenindex > playerp[0].total) {
				printf("card number must be less than %d\n", playerp[0].total);
			}
			else if (havecard == 1) {
				targetc = playerp[0].hcardp;
				while (targetc != NULL) {
					if (targetc->index == chosenindex) {
						chosenface = targetc->face;
						strcpy(suit, targetc->suit);
						break;
					}
					targetc = targetc->listp;
				}
				if (strcmp(suit, targetsuit) != 0) {
					printf("card must have same suit as lead card\n");
				}
				else { break; }
			}
			else {
				break;
			}
		}
		if (havecard == 0) {
			targetc = playerp[0].hcardp;
			while (targetc != NULL) {
				if (targetc->index == chosenindex) {
					chosenface = targetc->face;
					strcpy(suit, targetc->suit);
					break;
				}
				targetc = targetc->listp;
			}
		}
		//use index to return face and suit and use for choosecard func
		p0card = choosecard(playerp, p0card, chosenface, suit, 0);
		printf("Turn %d, %s plays: ", turn, playerp[0].name);
		printcard(p0card);

		targetc = playerp[1].hcardp;
		havecard = 0;
		maxface = 0;
		minface = 14;
		while (targetc != NULL) {
			if (strcmp(targetc->suit, targetsuit) == 0) {
				havecard = 1;
				break;
			}
			else { targetc = targetc->listp; }
		}
		targetc = playerp[1].hcardp;
		if (*heartbreak == 0) {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 1) {
						maxface = 1;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face > maxface) {
						maxface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 1) {
							maxface = 1;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face > maxface) {
							maxface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p1card = choosecard(playerp, p1card, maxface, suit, 1);
		}
		else {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 2) {
						minface = 2;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face < minface) {
						minface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 2) {
							minface = 2;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face < minface) {
							minface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p1card = choosecard(playerp, p1card, minface, suit, 1);
		}
		printf("Turn %d, %s plays: ", turn, playerp[1].name);
		printcard(p1card);

		printf("\n");
		printf("%s card is ", playerp[0].name);
		printcard(p0card);
		printf("%s card is ", playerp[1].name);
		printcard(p1card);
		printf("%s card is ", playerp[2].name);
		printcard(p2card);
		printf("%s card is ", playerp[3].name);
		printcard(p3card);
		printf("\n");
		winner = check(p0card, p1card, p2card, p3card, targetsuit, &total);
		pscore[winner] = pscore[winner] + total;
		printf("\n");
		printf("Turn %d: %s, %s, %s, %s have %d %d %d %d points\n", turn, playerp[0].name, playerp[1].name, playerp[2].name, playerp[3].name, pscore[0], pscore[1], pscore[2], pscore[3]);
		deletecard(&ptr[0].hcardp, &ptr[0].tcardp, p0card->suit, p0card->face);
		reassignindex(playerp[0].hcardp);
		deletecard(&ptr[1].hcardp, &ptr[1].tcardp, p1card->suit, p1card->face);
		reassignindex(playerp[1].hcardp);
		deletecard(&ptr[2].hcardp, &ptr[2].tcardp, p2card->suit, p2card->face);
		reassignindex(playerp[2].hcardp);
		deletecard(&ptr[3].hcardp, &ptr[3].tcardp, p3card->suit, p3card->face);
		reassignindex(playerp[3].hcardp);
		if (pscore[0] != 0 && pscore[0] != 13) {
			*heartbreak = 1;
		}
		if (pscore[1] != 0 && pscore[1] != 13) {
			*heartbreak = 1;
		}
		if (pscore[2] != 0 && pscore[2] != 13) {
			*heartbreak = 1;
		}
		if (pscore[3] != 0 && pscore[3] != 13) {
			*heartbreak = 1;
		}
		printf("***---***Hit any key to continue***---***");
		scanf(" %c", &c);
		printf("\n");
		printf("Hand after turn %d\n", turn);
		return winner;
	}
	if (targetindex == 3) {
		if (*first == 0) {
			targetc = playerp[3].hcardp;
			havecard = 0;
			maxface = 0;
			minface = 14;
			heartcard = 1;
			while (targetc != NULL) {
				if (strcmp(targetc->suit, DIAMOND) == 0 || strcmp(targetc->suit, CLUB) == 0 || strcmp(targetc->suit, SPADE) == 0) {
					heartcard = 0;
				}
				if (strcmp(targetc->suit, targetsuit) == 0) {
					havecard = 1;
					break;
				}
				else { targetc = targetc->listp; }
			}
			targetc = playerp[3].hcardp;
			if (*heartbreak == 0) {
				if (havecard == 0) {
					while (targetc != NULL) {
						if (heartcard == 1) {
							if (targetc->face == 1) {
								maxface = 1;
								strcpy(suit, targetc->suit);
								break;
							}
						}
						else if (heartcard == 0) {
							if (targetc->face == 1 && strcmp(targetc->suit, HEART) != 0) {
								maxface = 1;
								strcpy(suit, targetc->suit);
								break;
							}
						}
						if (heartcard == 1) {
							if (targetc->face > maxface) {
								maxface = targetc->face;
								strcpy(suit, targetc->suit);
							}
						}
						else if (heartcard == 0) {
							if (targetc->face > maxface && strcmp(targetc->suit, HEART) != 0) {
								maxface = targetc->face;
								strcpy(suit, targetc->suit);
							}
						}
						targetc = targetc->listp;
					}
				}
				if (havecard == 1) {
					while (targetc != NULL) {
						if (strcmp(targetc->suit, targetsuit) == 0) {
							if (targetc->face == 1) {
								maxface = 1;
								strcpy(suit, targetc->suit);
								break;
							}
							if (targetc->face > maxface) {
								maxface = targetc->face;
								strcpy(suit, targetc->suit);
							}
						}
						targetc = targetc->listp;
					}
				}
				p3card = choosecard(playerp, p3card, maxface, suit, 3);
			}
			else {
				if (havecard == 0) {
					while (targetc != NULL) {
						if (targetc->face == 2) {
							minface = 2;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face < minface) {
							minface = targetc->face;
							strcpy(suit, targetc->suit);
						}
						targetc = targetc->listp;
					}
				}
				if (havecard == 1) {
					while (targetc != NULL) {
						if (strcmp(targetc->suit, targetsuit) == 0) {
							if (targetc->face == 2) {
								minface = 2;
								strcpy(suit, targetc->suit);
								break;
							}
							if (targetc->face < minface) {
								minface = targetc->face;
								strcpy(suit, targetc->suit);
							}
						}
						targetc = targetc->listp;
					}
				}
				p3card = choosecard(playerp, p3card, minface, suit, 3);
			}
			printf("Turn %d, %s will lead with: ", turn, playerp[3].name);
			printcard(p3card);
		}
		else if (*first == 1) {
		targetc = playerp[3].hcardp;
		while (targetc != NULL) {
			if (targetc->face == 2 && strcmp(targetc->suit, CLUB) == 0) {
				p3card = targetc;
			}
			targetc = targetc->listp;
		}
			*first = 0;
			printf("Turn %d, %s will lead with ", turn, playerp[3].name);
			printcard(p3card);
		}
		printf("Turn %d, %s plays: ", turn, playerp[3].name);
		printcard(p3card);

		strcpy(targetsuit, p3card->suit);

		while (1) {
			printf("Enter card number between 1-%d where 1 is the leftmost card: ", playerp[0].total);
			scanf("%d", &chosenindex);
			printf("\n");
			havecard = 0;
			targetc = playerp[0].hcardp;
			while (targetc != NULL) {
				if (strcmp(targetc->suit, targetsuit) == 0) {
					havecard = 1;
					break;
				}
				else { targetc = targetc->listp; }
			}
			if (chosenindex <= 0) {
				printf("card number must be greater than 0\n");
			}
			else if (chosenindex > playerp[0].total) {
				printf("card number must be less than %d\n", playerp[0].total);
			}
			else if (havecard == 1) {
				targetc = playerp[0].hcardp;
				while (targetc != NULL) {
					if (targetc->index == chosenindex) {
						chosenface = targetc->face;
						strcpy(suit, targetc->suit);
						break;
					}
					targetc = targetc->listp;
				}
				if (strcmp(suit, targetsuit) != 0) {
					printf("card must have same suit as lead card\n");
				}
				else { break; }
			}
			else {
				break;
			}
		}
		if (havecard == 0) {
			targetc = playerp[0].hcardp;
			while (targetc != NULL) {
				if (targetc->index == chosenindex) {
					chosenface = targetc->face;
					strcpy(suit, targetc->suit);
					break;
				}
				targetc = targetc->listp;
			}
		}
		//use index to return face and suit and use for choosecard func
		p0card = choosecard(playerp, p0card, chosenface, suit, 0);
		printf("Turn %d, %s plays: ", turn, playerp[0].name);
		printcard(p0card);


		targetc = playerp[1].hcardp;
		havecard = 0;
		maxface = 0;
		minface = 14;
		while (targetc != NULL) {
			if (strcmp(targetc->suit, targetsuit) == 0) {
				havecard = 1;
				break;
			}
			else { targetc = targetc->listp; }
		}
		targetc = playerp[1].hcardp;
		if (*heartbreak == 0) {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 1) {
						maxface = 1;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face > maxface) {
						maxface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 1) {
							maxface = 1;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face > maxface) {
							maxface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p1card = choosecard(playerp, p1card, maxface, suit, 1);
		}
		else {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 2) {
						minface = 2;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face < minface) {
						minface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 2) {
							minface = 2;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face < minface) {
							minface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p1card = choosecard(playerp, p1card, minface, suit, 1);
		}
		printf("Turn %d, %s plays: ", turn, playerp[1].name);
		printcard(p1card);

		targetc = playerp[2].hcardp;
		havecard = 0;
		maxface = 0;
		minface = 14;
		while (targetc != NULL) {
			if (strcmp(targetc->suit, targetsuit) == 0) {
				havecard = 1;
				break;
			}
			else { targetc = targetc->listp; }
		}
		targetc = playerp[2].hcardp;
		if (*heartbreak == 0) {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 1) {
						maxface = 1;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face > maxface) {
						maxface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 1) {
							maxface = 1;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->face > maxface) {
							maxface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p2card = choosecard(playerp, p2card, maxface, suit, 2);
		}
		else {
			if (havecard == 0) {
				while (targetc != NULL) {
					if (targetc->face == 2) {
						minface = 2;
						strcpy(suit, targetc->suit);
						break;
					}
					if (targetc->face < minface) {
						minface = targetc->face;
						strcpy(suit, targetc->suit);
					}
					targetc = targetc->listp;
				}
			}
			if (havecard == 1) {
				while (targetc != NULL) {
					if (strcmp(targetc->suit, targetsuit) == 0) {
						if (targetc->face == 2) {
							minface = 2;
							strcpy(suit, targetc->suit);
							break;
						}
						if (targetc->index < minface) {
							minface = targetc->face;
							strcpy(suit, targetc->suit);
						}
					}
					targetc = targetc->listp;
				}
			}
			p2card = choosecard(playerp, p2card, minface, suit, 2);
		}
		printf("Turn %d, %s plays: ", turn, playerp[2].name);
		printcard(p2card);

		printf("\n");
		printf("%s card is ", playerp[0].name);
		printcard(p0card);
		printf("%s card is ", playerp[1].name);
		printcard(p1card);
		printf("%s card is ", playerp[2].name);
		printcard(p2card);
		printf("%s card is ", playerp[3].name);
		printcard(p3card);
		printf("\n");
		winner = check(p0card, p1card, p2card, p3card, targetsuit, &total);
		pscore[winner] = pscore[winner] + total;
		printf("\n");
		printf("Turn %d: %s, %s, %s, %s have %d %d %d %d points\n", turn, playerp[0].name, playerp[1].name, playerp[2].name, playerp[3].name, pscore[0], pscore[1], pscore[2], pscore[3]);
		deletecard(&ptr[0].hcardp, &ptr[0].tcardp, p0card->suit, p0card->face);
		reassignindex(playerp[0].hcardp);
		deletecard(&ptr[1].hcardp, &ptr[1].tcardp, p1card->suit, p1card->face);
		reassignindex(playerp[1].hcardp);
		deletecard(&ptr[2].hcardp, &ptr[2].tcardp, p2card->suit, p2card->face);
		reassignindex(playerp[2].hcardp);
		deletecard(&ptr[3].hcardp, &ptr[3].tcardp, p3card->suit, p3card->face);
		reassignindex(playerp[3].hcardp);
		if (pscore[0] != 0 && pscore[0] != 13) {
			*heartbreak = 1;
		}
		if (pscore[1] != 0 && pscore[1] != 13) {
			*heartbreak = 1;
		}
		if (pscore[2] != 0 && pscore[2] != 13) {
			*heartbreak = 1;
		}
		if (pscore[3] != 0 && pscore[3] != 13) {
			*heartbreak = 1;
		}
		printf("***---***Hit any key to continue***---***");
		scanf(" %c", &c);
		printf("\n");
		printf("Hand after turn %d\n", turn);
		return winner;
	}
}
int main(void) {
	//Variable assignments
	card *headp = NULL, *temp, *tail = NULL;
	char symbol[2];
	int i, j;
	int count = 0;
	char cont = 'y';
	while (cont != 'q' && cont != 'Q') {
		//Creating the deck
		temp = (card*)malloc(sizeof(card));
		for (i = 0; i < 4; i++) {
			for (j = 1; j <= 13; j++) {
				if (i == 0) {
					symbol[0] = 'S';
					symbol[1] = '\0';
					temp->face = j;
					strcpy(temp->suit, SPADE);
				}
				else if (i == 1) {
					symbol[0] = 'H';
					symbol[1] = '\0';
					temp->face = j;
					strcpy(temp->suit, HEART);
				}
				else if (i == 2) {
					symbol[0] = 'C';
					symbol[1] = '\0';
					temp->face = j;
					strcpy(temp->suit, CLUB);
				}
				else if (i == 3) {
					symbol[0] = 'D';
					symbol[1] = '\0';
					temp->face = j;
					strcpy(temp->suit, DIAMOND);
				}
				count++;
				temp->index = count;
				if (headp == NULL) //make headp point to the location that temp points to 
					headp = temp;
				else {
					tail->listp = temp;
				}
				tail = temp; 		// updating tail
				tail->listp = NULL; 	// setting next pt. of tail to null.
									//allocate the memory for the next (new) node
				temp = (card*)malloc(sizeof(card));
			}
		}
		printf("*****Before Shuffle*****\n");
		printdeck(headp);
		card** pheadp = &headp;
		card** ptailp = &tail;
		//Shuffle the deck
		printf("*****After Shuffle*****\n");
		reassignindex(headp);
		shuffle(headp);
		printdeck(headp);
		player* ptr;
		char pname[MAX];
		//Create players
		ptr = (player*)malloc(sizeof(player) * 4);
		printf("Enter your name: ");
		scanf("%s", pname);
		printf("xxx---xxx xxx---xxx xxx---xxx\n");
		strcpy(ptr[0].name, pname);
		printf("%s, Let's play Hearts\n", pname);
		printf("xxx---xxx xxx---xxx xxx---xxx\n");
		ptr[0].index = 0;
		ptr[0].total = 13;
		ptr[0].hcardp = NULL;
		ptr[0].tcardp = NULL;
		strcpy(ptr[1].name, "COM1");
		ptr[1].index = 1;
		ptr[1].total = 13;
		ptr[1].hcardp = NULL;
		ptr[1].tcardp = NULL;
		strcpy(ptr[2].name, "COM2");
		ptr[2].index = 2;
		ptr[2].total = 13;
		ptr[2].hcardp = NULL;
		ptr[2].tcardp = NULL;
		strcpy(ptr[3].name, "COM3");
		ptr[3].index = 3;
		ptr[3].total = 13;
		ptr[3].hcardp = NULL;
		ptr[3].tcardp = NULL;
		card* targetp = headp;
		card* prev;
		int p1num = 0, p2num = 0, p3num = 0, p4num = 0;
		//Share cards while deleting them from deck
		while (targetp != NULL) {
			if (ptr[0].hcardp == NULL) //make headp point to the location that temp points to 
				ptr[0].hcardp = targetp;
			else {
				ptr[0].tcardp->listp = targetp;
			}
			ptr[0].tcardp = targetp; 		// updating tail	// setting next pt. of tail to null.
			prev = targetp;					     //allocate the memory for the next (new) node
			targetp = targetp->listp;
			ptr[0].tcardp->listp = NULL;
			p1num++;
			if (headp != NULL) {
				headp = headp->listp;
			}
			deletecard(pheadp, ptailp, prev->suit, prev->face);



			if (ptr[1].hcardp == NULL) //make headp point to the location that temp points to 
				ptr[1].hcardp = targetp;
			else {
				ptr[1].tcardp->listp = targetp;
			}
			ptr[1].tcardp = targetp; 		// updating tail	// setting next pt. of tail to null.
			prev = targetp;					//allocate the memory for the next (new) node
			targetp = targetp->listp;
			ptr[1].tcardp->listp = NULL;
			p2num++;
			if (headp != NULL) {
				headp = headp->listp;
			}
			deletecard(pheadp, ptailp, prev->suit, prev->face);

			if (ptr[2].hcardp == NULL) //make headp point to the location that temp points to 
			{
				ptr[1];
				ptr[2].hcardp = targetp;
			}
			else {
				ptr[2].tcardp->listp = targetp;
			}
			ptr[2].tcardp = targetp; 		// updating tail	// setting next pt. of tail to null.
			prev = targetp;					//allocate the memory for the next (new) node
			targetp = targetp->listp;
			ptr[2].tcardp->listp = NULL;
			p3num++;
			if (headp != NULL) {
				headp = headp->listp;
			}
			deletecard(pheadp, ptailp, prev->suit, prev->face);

			if (ptr[3].hcardp == NULL) //make headp point to the location that temp points to 
				ptr[3].hcardp = targetp;
			else {
				ptr[3].tcardp->listp = targetp;
			}
			ptr[3].tcardp = targetp; 		// updating tail	// setting next pt. of tail to null.
			prev = targetp;					//allocate the memory for the next (new) node
			targetp = targetp->listp;
			ptr[3].tcardp->listp = NULL;
			p4num++;
			if (headp != NULL) {
				headp = headp->listp;
			}
			deletecard(pheadp, ptailp, prev->suit, prev->face);
		}
		//Sort cards in player's hands
		selection(ptr[0].hcardp);
		selection(ptr[1].hcardp);
		selection(ptr[2].hcardp);
		selection(ptr[3].hcardp);
		//Reassign all index in new hand's
		reassignindex(ptr[0].hcardp);
		reassignindex(ptr[1].hcardp);
		reassignindex(ptr[2].hcardp);
		reassignindex(ptr[3].hcardp);
		printf("%s's hand has %d cards\n", pname, p1num);
		printdeck(ptr[0].hcardp);
		//printf("Computer 1's hand has %d cards\n", p2num);
		//printdeck(ptr[1].hcardp);
		//printf("Computer 2's hand has %d cards\n", p3num);
		//printdeck(ptr[2].hcardp);
		//printf("Computer 3's hand has %d cards\n", p4num);
		//printdeck(ptr[3].hcardp);

		//Determination of which cards to pass implementing computer strategy by making computer pass their large cards
		int p1pass[3];
		int p2pass[3];
		int p3pass[3];
		int p4pass[3];
		while (1) {
			printf("Choose 3 cards to give away\n");
			printf("Enter card number between 1-13 where 1 is the leftmost card: ");
			scanf("%d %d %d", &p1pass[0], &p1pass[1], &p1pass[2]);
			printf("\n");
			for (i = 0; i < 3; i++) {
				if (p1pass[i] <= 0) {
					printf("card number must be greater than 0\n");
					break;
				}
				if (p1pass[i] > 13) {
					printf("card number must be less than 13\n");
					break;
				}
				if (i == 0) {
					if (p1pass[i] == p1pass[i + 1] || p1pass[i] == p1pass[i + 2] || p1pass[i + 1] == p1pass[i + 2]) {
						printf("All 3 numbers must be different\n");
						break;
					}
				}
			}
			if (i == 3) {
				break;
			}
		}
		for (i = 0; i < 3; i++) {
			p2pass[i] = 0;
			p3pass[i] = 0;
			p4pass[i] = 0;
		}
		int maxface;
		for (i = 0; i < 3; i++) {
			maxface = 0;
			targetp = ptr[1].hcardp;
			while (targetp != NULL) {
				if (targetp->face == 1) {
					if (targetp->index != p2pass[0] && targetp->index != p2pass[1] && targetp->index != p2pass[2]) {
						maxface = targetp->face;
						p2pass[i] = targetp->index;
						break;
					}
				}
				if (targetp->face >= maxface) {
					if (targetp->index != p2pass[0] && targetp->index != p2pass[1] && targetp->index != p2pass[2]) {
						maxface = targetp->face;
						p2pass[i] = targetp->index;
					}
				}
				targetp = targetp->listp;
			}

			maxface = 0;
			targetp = ptr[2].hcardp;
			while (targetp != NULL) {
				if (targetp->face == 1) {
					if (targetp->index != p3pass[0] && targetp->index != p3pass[1] && targetp->index != p3pass[2]) {
						maxface = targetp->face;
						p3pass[i] = targetp->index;
						break;
					}
				}
				if (targetp->face >= maxface) {
					if (targetp->index != p3pass[0] && targetp->index != p3pass[1] && targetp->index != p3pass[2]) {
						maxface = targetp->face;
						p3pass[i] = targetp->index;
					}
				}
				targetp = targetp->listp;
			}

			maxface = 0;
			targetp = ptr[3].hcardp;
			while (targetp != NULL) {
				if (targetp->face == 1) {
					if (targetp->index != p4pass[0] && targetp->index != p4pass[1] && targetp->index != p4pass[2]) {
						maxface = targetp->face;
						p4pass[i] = targetp->index;
						break;
					}
				}
				if (targetp->face >= maxface) {
					if (targetp->index != p4pass[0] && targetp->index != p4pass[1] && targetp->index != p4pass[2]) {
						maxface = targetp->face;
						p4pass[i] = targetp->index;
					}
				}
				targetp = targetp->listp;
			}
		}

		//Adding chosen cards to new hands
		targetp = NULL;
		card* target1 = NULL;
		card* target2 = NULL;
		card* target3 = NULL;
		targetp = ptr[0].hcardp;
		while (targetp != NULL) {
			if (targetp->index == p1pass[0]) {
				target1 = targetp;
			}
			if (targetp->index == p1pass[1]) {
				target2 = targetp;
			}
			if (targetp->index == p1pass[2]) {
				target3 = targetp;
			}
			targetp = targetp->listp;
		}
		addcard(ptr, target1, 1);
		addcard(ptr, target2, 1);
		addcard(ptr, target3, 1);
		reassignindex(ptr[1].hcardp);


		targetp = NULL;
		target1 = NULL;
		target2 = NULL;
		target3 = NULL;
		targetp = ptr[1].hcardp;
		while (targetp != NULL) {
			if (targetp->index == p2pass[0]) {
				target1 = targetp;
			}
			if (targetp->index == p2pass[1]) {
				target2 = targetp;
			}
			if (targetp->index == p2pass[2]) {
				target3 = targetp;
			}
			targetp = targetp->listp;
		}
		addcard(ptr, target1, 2);
		addcard(ptr, target2, 2);
		addcard(ptr, target3, 2);
		reassignindex(ptr[2].hcardp);


		targetp = NULL;
		target1 = NULL;
		target2 = NULL;
		target3 = NULL;
		targetp = ptr[2].hcardp;
		while (targetp != NULL) {
			if (targetp->index == p3pass[0]) {
				target1 = targetp;
			}
			if (targetp->index == p3pass[1]) {
				target2 = targetp;
			}
			if (targetp->index == p3pass[2]) {
				target3 = targetp;
			}
			targetp = targetp->listp;
		}
		addcard(ptr, target1, 3);
		addcard(ptr, target2, 3);
		addcard(ptr, target3, 3);
		reassignindex(ptr[3].hcardp);


		targetp = NULL;
		target1 = NULL;
		target2 = NULL;
		target3 = NULL;
		targetp = ptr[3].hcardp;
		while (targetp != NULL) {
			if (targetp->index == p4pass[0]) {
				target1 = targetp;
			}
			if (targetp->index == p4pass[1]) {
				target2 = targetp;
			}
			if (targetp->index == p4pass[2]) {
				target3 = targetp;
			}
			targetp = targetp->listp;
		}
		addcardtop1(ptr, target1);
		addcardtop1(ptr, target2);
		addcardtop1(ptr, target3);
		reassignindex(ptr[0].hcardp);


		printf("%s's New hand has %d cards\n", pname, p1num);
		printdeck(ptr[0].hcardp);
		//Sorting new hands
		selection2(ptr[0].hcardp);
		selection2(ptr[1].hcardp);
		selection2(ptr[2].hcardp);
		selection2(ptr[3].hcardp);
		//Reassign index again
		reassignindex(ptr[0].hcardp);
		reassignindex(ptr[1].hcardp);
		reassignindex(ptr[2].hcardp);
		reassignindex(ptr[3].hcardp);
		printf("After Sorting\n");
		printf("%s's New hand has %d cards\n", pname, p1num);
		printdeck(ptr[0].hcardp);
		//printf("Computer 1's New hand has %d cards\n", p2num);
		//printdeck(ptr[1].hcardp);
		//printf("Computer 2's New hand has %d cards\n", p3num);
		//printdeck(ptr[2].hcardp);
		//printf("Computer 3's New hand has %d cards\n", p4num);
		//printdeck(ptr[3].hcardp);

		//Determination of first lead player
		player* targetpla = NULL;
		targetpla = ptr;
		card* targetcard = NULL;
		int targetindex;
		for (i = 0; i < 4; i++) {
			targetcard = targetpla[i].hcardp;
			while (targetcard != NULL) {
				if (targetcard->face == 2) {
					if (strcmp(targetcard->suit, CLUB) == 0) {
						targetindex = i;
					}
				}
				targetcard = targetcard->listp;
			}
		}
		printf("\n");
		//Variable definitions needed for roundfunction
		int tempindex;
		int heartbreak = 0;
		int first = 1;
		int* pheartbreak = &heartbreak;
		int* pfirst = &first;
		int pscore[4];
		pscore[0] = 0;
		pscore[1] = 0;
		pscore[2] = 0;
		pscore[3] = 0;
		/*Implementation of round function 13 times
		Note: Round function implements computer strategy by making computer play largest cards while
		heart isn't broken to get rid of big cards and smallest cards after heart is broken to reduce
		chances of getting a heart card (Heart break occurs when heart has been played once)
		Note: Restrictions that apply in round function:
		Cannot play heart until you dont have leaders suit in hand or heart has previously been broken
		Can only play card between index 1 and the total prresently in hand
		*/
		for (i = 1; i <= 13; i++) {
			printf("%s's New hand has %d cards\n", pname, ptr[0].total);
			printdeck(ptr[0].hcardp);
			//printf("Computer 1's New hand has %d cards\n", ptr[1].total);
			//printdeck(ptr[1].hcardp);
			//printf("Computer 2's New hand has %d cards\n", ptr[2].total);
			//printdeck(ptr[2].hcardp);
			//printf("Computer 3's New hand has %d cards\n", ptr[3].total);
			//printdeck(ptr[3].hcardp);
			//Fix delete round func...only deletes for p1??
			tempindex = roundfunction(ptr, targetindex, pheartbreak, pfirst, i, &pscore);
			targetindex = tempindex;
			reassignindex(ptr[0].hcardp);
			reassignindex(ptr[1].hcardp);
			reassignindex(ptr[2].hcardp);
			reassignindex(ptr[3].hcardp);
			ptr[0].total--;
			ptr[1].total--;
			ptr[2].total--;
			ptr[3].total--;
			printf("\n");
		}
		//Final Scores
		printf("End of game: %s, %s, %s, %s have %d %d %d %d points\n", ptr[0].name, ptr[1].name, ptr[2].name, ptr[3].name, pscore[0], pscore[1], pscore[2], pscore[3]);
		int minscore = 27;
		for (i = 0; i < 4; i++) {
			if (pscore[i] < minscore) {
				minscore = pscore[i];
			}
		}
		//Declaration of Winner/Winners
		if (minscore == pscore[0]) {
			printf("Congratulations, %s, you win the game!!\n", ptr[0].name);
		}
		if (minscore == pscore[1]) {
			printf("Congratulations, %s, you win the game!!\n", ptr[1].name);
		}
		if (minscore == pscore[2]) {
			printf("Congratulations, %s, you win the game!!\n", ptr[2].name);
		}
		if (minscore == pscore[3]) {
			printf("Congratulations, %s, you win the game\n!!", ptr[3].name);
		}
		printf("Do you want to quit (q/Q to quit)?");
		scanf(" %c", &cont);
	}
	/*Fix delete round doesnt delete head
	fix heart break cond to OR not AND
	Add condition to not play heart until absolutely necessary*/
/*
PART 3
Skeleton:
Requests the user to select 3 cards to pass on to next player and stores the values in an integer array
In order to make the computer smart it passes its three largest values. So, using loop get the positions(index) of the three largest cards and store in an integer array.
Creates 3 card pointers and uses them to point to the cards whose indexes are in the inter array (hence largest cards)
Add them to the next player and delete them from the previous player. This is done with the addcard function whose input are the pointers pointing to the cars to be passed. (Order: User->CPU1->CPU2->CPU3->User)
Requests the player who has 2 clubs to start the game with 2 clubs and requests a card from the user if they are not with 2 clubs and the other 2 computer players play their largest cards. Person with largest card is declared winner of round.
Using a round function to represent each subsequent round: Leader (winner of previous round) plays a card that is not hearts. Requests card from user if they are not the leader and while hearts and Q spade has not yet been played the computer will play the largest card that is not Q spade that is the same suit as the leader’s card if no card available with same suit then allow any suit to be picked. The rule of not playing heart until it’s been played by someone else or if the player does not have the suit of the leader in their hand applies to the User and CPUs. Once heart has been played the computers begin playing their smallest cards and once K spade or A spade is played the computer with Q spade should play it to effectively avoid getting 13 points.
Every card played is deleted from its respective linked list and added to one of the four created card arrays named bag based on the winner of that round. A loop function goes through all cards in the bags and outputs the score with each heart card a +1 and a Q spade card a +13
Once 12 subsequent rounds have been played then declare the overall winner as the person with smallest points.
*/
}
