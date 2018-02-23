/*

Azizul Hakim
COP 3223C
MWF 1:30-2:20
Black Jack

*/


#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CLUBS 0
#define DIAMONDS 1
#define HEARTS 2
#define SPADES 3


enum{ TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

int Deck[52];
int CurrentDealCard;
int Dealer[20], Player[20];
int DealerCards, PlayerCards;
int DealerScore, PlayerScore;
int choice;
int choice2;
int CardsDealt;

void DoShuffle()
{
	int i, nextcard;
	int Used[52];

	/* Here we clear out Used array to zeros, which indicates no
	   values have been used. */
	for (i = 0; i < 52; i++) Used[i] = 0;

	/* Loop through the deck of cards, there are 52 values */
	for (i = 0; i < 52; i++)
	{
		/* Here we used a do-while. If the card has already been used,
		   we need to keep generating random numbers until we find a card
		   that has not been used. */
		do
		{
			nextcard = rand() % 52; /* Value from 0 to 51 */

		} while (Used[nextcard] == 1); /* This is our check */


		/* Here we set to 1 so that we remember that this card has been used */
		Used[nextcard] = 1;

		/* Finally, put the card in the deck. */
		Deck[i] = nextcard;
	}
}

void DrawCard(int rank, int suit)
{

	switch (rank)
	{
	case TWO:
		printf("Two ");
		break;
	case THREE:
		printf("Three ");
		break;
	case FOUR:
		printf("Four ");
		break;
	case FIVE:
		printf("Five ");
		break;
	case SIX:
		printf("Six ");
		break;
	case SEVEN:
		printf("Seven ");
		break;
	case EIGHT:
		printf("Eight ");
		break;
	case NINE:
		printf("Nine ");
		break;
	case TEN:
		printf("Ten ");
		break;
	case JACK:
		printf("Jack ");
		break;
	case QUEEN:
		printf("Queen ");
		break;
	case KING:
		printf("King ");
		break;
	case ACE:
		printf("Ace ");
		break;
	}

	switch (suit)
	{
	case CLUBS:
		printf("Clubs");
		break;
	case DIAMONDS:
		printf("Diamonds");
		break;
	case HEARTS:
		printf("Hearts");
		break;
	case SPADES:
		printf("Spades");
		break;
	}

}

void DisplayShuffledDeck()
{
	int i, suit, rank;

	for (i = 0; i < 52; i++)
	{
		suit = Deck[i] / 13;
		rank = Deck[i] % 13;
		DrawCard(rank, suit);
		printf("\n");
	}

}

void DealCards()
{
	PlayerCards = DealerCards = CurrentDealCard = 0;

	Player[PlayerCards++] = Deck[CurrentDealCard++];
	CardsDealt++;
	Dealer[DealerCards++] = Deck[CurrentDealCard++];
	Player[PlayerCards++] = Deck[CurrentDealCard++];
	CardsDealt++;
	if (choice == 2)
	Dealer[DealerCards++] = Deck[CurrentDealCard++];

}

void DisplayDealtCards()
{
	int i;

	printf("\n\n\nDealer:\n");
	for (i = 0; i < DealerCards; i++) DrawCard(Dealer[i] % 13, Dealer[i] / 13), printf( "    " );
	printf("Dealer Score is %d\n\n\nPlayer:\n", DealerScore);
	for (i = 0; i < PlayerCards; i++) DrawCard(Player[i] % 13, Player[i] / 13), printf("    ");
	printf("Player Score is %d\n\n\n", PlayerScore);

}

void DisplayChoice()
{
	printf("What would you like to do?\n");
	printf("1. Hit\n2. Stand\n");
}

int GetChoice(int min, int max)
{

	do
	{
		printf("Make a choice from %d to %d:", min, max);
		scanf("%d", &choice);
	} while (choice < min || choice > max);

	return(choice);
}

void CalculateScores()
{
	int i, rank, suit, ace=0;

	PlayerScore = 0;
	for (i = 0; i < PlayerCards; i++)
	{
		rank = Player[i] % 13;
		suit = Player[i] / 13;

		if (rank >= TWO && rank <= TEN) PlayerScore += (rank + 2);

		else if (rank >= JACK && rank <= KING) PlayerScore += 10;
		else if (rank = ACE )
        {

            if(PlayerScore <= 10)
            {
                ace++;
                PlayerScore+=11;
            }

            else if(PlayerScore > 10)
            {
                PlayerScore+=1;

            }

        }
        if(PlayerScore > 21 && ace==1)
        {
            PlayerScore-=10;
            ace=0;
        }
	}

	DealerScore = 0;
	for (i = 0; i < DealerCards; i++)
	{
		rank = Dealer[i] % 13;
		suit = Dealer[i] / 13;

		if (rank >= TWO && rank <= TEN) DealerScore += (rank + 2);

		else if (rank >= JACK && rank <= KING) DealerScore += 10;

		else DealerScore += 11;
	}

}
void DoubleDown()
{
    Player[PlayerCards++] = Deck[CurrentDealCard++];
    CalculateScores();
    DisplayDealtCards();

}

int main()
{
    int choice;
	int secondchoice, i;

	srand(time(0));

	DoShuffle();

	DealCards();
	CalculateScores();
	DisplayDealtCards();
	if (CardsDealt == 1 || CardsDealt == 2)
    {
        printf("Would you like to double down?\n");
        printf("1. Yes\n2. No\n");
        scanf("%d", &choice);
        if (choice == 1)
            {
                DoubleDown();
                printf("Your wager has been doubled\n");
                CalculateScores();

            }
    }

	DisplayChoice();
	choice = GetChoice(1, 2);
	if (choice == 1)
	{
		Player[PlayerCards++] = Deck[CurrentDealCard++];
		CalculateScores();
		DisplayDealtCards();
		if ( PlayerScore == 9 || PlayerScore == 10 || PlayerScore == 11)
        {
            printf("Would you like to double down?\n Press 1 for yes, or 2 for no.");
            choice = GetChoice(1, 2);
            if (choice == 1)
                {
                    DoubleDown();

                }
                else
                {
                    CalculateScores();
                }
        }
		while (PlayerScore < 21 )
        {
            printf("Would you like to go again?\n Press 1 for yes, or 2 to stand.");
            scanf("%d", &choice);
            if (choice == 1)
            {
                Player[PlayerCards++] = Deck[CurrentDealCard++];
                CalculateScores();
                DisplayDealtCards();
            }
            else
            {
                Dealer[DealerCards++] = Deck[CurrentDealCard++];
                if ( DealerScore <17 )
                {Dealer[DealerCards++] = Deck[CurrentDealCard++];}

                CalculateScores();
                DisplayDealtCards();

                break;
            }

        }

	}

	else
    {
        Dealer[DealerCards++] = Deck[CurrentDealCard++];
        if (DealerScore < 17)
            {
                Dealer[DealerCards++] = Deck[CurrentDealCard++];
            }

        CalculateScores();
        DisplayDealtCards();

    }


	return 0;
}
