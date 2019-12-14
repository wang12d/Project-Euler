#include <bits/stdc++.h>
#include <random>
#define M 40

using namespace std;


pair<int, int> cards[M];  // cards

int current_pointer = 0;   // the location of cardme
/*
 * -1: do nothing
 * -2: Move to next R
 * -3: Backward 3
 * -4: Move to next U
 */
int cc_pointer = 0; 
int ch_pointer = 0;
int CC[16] = {0, 10};
int CH[16] = {0, 10, 11, 24, 39, 5, -2, -2, -4, -3};
int cc[M];
int ch[M];
int p[2], pp[2], cur[2];

void move_next_R()
{
  if (current_pointer == 7)
    {
      current_pointer = 15;
    }
  else if (current_pointer == 22)
    {
      current_pointer = 25;
    }
  else
    {
      current_pointer = 5; 
    }
}

void move_next_U()
{
  if (current_pointer == 7 || current_pointer == 36)
    {
      current_pointer = 12;
    }
  else
    {
      current_pointer = 28;
    }
}

void goto_jail()
{
  current_pointer = 10;
}

void com_chest()
{
  
  int c = CC[cc_pointer];
  cc_pointer = (cc_pointer + 1) % 16;
  if (c >= 0)
    {
      current_pointer = c;
    }
}

bool too_many()
{
  return pp[0] == pp[1] && p[0] == p[1] && cur[0] == cur[1];
}

int main(int argc, char *argv[])
{
  int i;
  for (i = 2; i < 16; ++i)
    {
      CC[i] = -1;
      i >= 10 ? CH[i] = -1 : CH[i] = CH[i];
    }
  // init cards
  for (i = 0; i < M; ++i)
    {
      cards[i] = make_pair(0, i);
    }
  ++cards[0].first;
  cc[2] = cc[17] = cc[33] = 1;
  ch[7] = ch[22] = ch[36] = 1;
  
  unsigned seed = 0;
  shuffle(CH, CH+16, default_random_engine(seed));
  shuffle(CC, CC+16, default_random_engine(seed));

  int n = atoi(argv[1]);  // the max die
  int m = atoi(argv[2]); // the number of trial times
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> uni(1, n);

  int r1, r2;   // first and second roll
  int repeat = 0;  // repeat times
  while (m--)
    {
      r1 = uni(rng);
      r2 = uni(rng);
      pp[0] = p[0];
      pp[1] = p[1];
      p[0] = cur[0];
      p[1] = cur[1];
      cur[0] = r1;
      cur[1] = r2;
      
      if (too_many())
	{
	  cur[0] = -1;
	  goto_jail();
	  ++cards[current_pointer].first;
	  continue;
	}
      int roll = r1 + r2;
      current_pointer = (current_pointer + roll) % M;
      if (current_pointer == 30)
	{
	  goto_jail();
	}
      // act of cc card
      else if (cc[current_pointer])
	{
	  com_chest();
	}
      // act of ch card
      else if (ch[current_pointer])
	{
	  int c = CH[ch_pointer];
	  ch_pointer = (ch_pointer + 1) % 16;
	  if (c >= 0)
	    {
	      current_pointer = c;
	    }
	  else if (c == -2)
	    {
	      move_next_R();
	    }
	  else if (c == -4)
	    {
	      move_next_U();
	    }
	  else if (c == -3)
	    {
	      current_pointer += c;
	      if (cc[current_pointer])
		{
		  com_chest();
		}
	    }
	}
      ++cards[current_pointer].first;
    }
  sort(cards, cards+M);
  for (i = 1; i < 4; ++i)
    {
      printf("%02d", cards[M-i].second);
    }
  printf("\n");
}
