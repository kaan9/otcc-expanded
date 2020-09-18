#include <stdio.h>
#include <stdlib.h>

#define ALLOC_LEN 99999

FILE *f; /* f (formerly Q) was an int which works fine on 32-bit 386 but can lose info on other systems */
int ch; /* should this be a char? */
char *D, *R; 
long v, q, ac, P, d, z, C, K, G, L, W, M;

E(e) /* add smth to a stack? */
{
	*(char*)D++ = e;
}

o()	/* get input function? */
{
	if (L) {
		ch = *(char*)L++;
		if (ch == 2) {
			L = 0;
			ch = W;
		}
	} else {
		ch = fgetc(f);
		printf("ch = %c -- %x\n", ch, ch);
	}
}

ch_is_id()
{
	return isalnum(ch) | ch == '_';
}

Y()
{
	if (ch == '\\') {
		o();
		if (ch == 'n')
			ch = '\n';
	}
}

ad()
{
	int e, j, m;
	while (isspace(ch) | ch == '#') {
		if (ch == '#') { /* handle preprocessor directive? */
			o();
			ad();
			if (d == 0x218) {
				ad();
				E(' ');
				*(int*)d = 1;
				*(int*)(d + 4) = D;
			}
			while (ch != '\n') {
				E(ch);
				o();
			}
			E(ch);
			E(2);
		}
		o();
	}
	C = 0;
	d = ch;
	if (ch_is_id()) {
		E(' ');
		M = D;
		while (ch_is_id()) {
			E(ch);
			o();
		}
		if (isdigit(d)) {
			z = strtol(M, 0, 0);
			d = 2;
		} else {
			*(char*)D = ' ';
			d = strstr(R, M - 1) - R;
			*(char*)D = 0;
			d = d * 8 + 0x100;
			if (d > 0x218) {
				d = P + d;
				if (*(int*)d == 1) {
					L = *(int*)(d + 4);
					W = ch;
					o();
					ad();
				}
			}
		}
	} else {
		o();
		if (d == '\'') {
			d = 2;
			Y();
			z = ch;
			o();
			o();
		} else if (d == '/' & ch == '*') { /* comment handling text? */
			o();
			while (ch) {
				while (ch != '*')
					o();
				o();
				if (ch == '/')
					ch = 0;
			}
			o();
			ad();
		} else {
			e = "++#m--%am*@R<^1c/@%[_[H3c%@%[_[H3c+@.B#d-@%:_^BKd<<Z/03e>>`/03e<=0f>=/f<@.f>@1f==&g!='g&&k||#l&@.BCh^@.BSi|@.B+j~@/%Yd!@&d*@b";
			while (j = *(char*)e++) {
				m = *(char*)e++;
				z = 0;
				while ((C = *(char*)e++ - 'b') < 0)
					z = z * 64 + C + 64;
				if (j == d & (m == ch | m == 64)) { /* 64 == @ ? */
					if (m == ch) {
						o();
						d = 1;
					}
					break;
				}
			}
		}
	}
}

ae(g)
{
	while (g && g != -1) {
		*(char*)q++ = g;
		g = g >> 8;
	}
}

A(e)
{
	int g;
	while (e) {
		g = *(int*)e;
		*(int*)e = q - e - 4;
		e = g;
	}
}

s(g, e)
{
	ae(g);
	*(int*)q = e;
	e = q;
	q = q + 4;
	return e;
}

H(e)
{
	s(0xb8, e);
}

B(e)
{
	return s(0xe9, e);
}

S(j, e)
{
	ae(0x0fc085); /* is this an instruction? */
	return s(0x84 + j, e);
}

Z(e)
{
	ae(0xc139); 
	H(0);
	ae(0x0f);
	ae(e + 0x90);
	ae(0xc0);
}

N(j, e)
{
	ae(j + 0x83);
	s((e < 0x200) << 7 | 5, e);
}

T(j)
{
	int g, e, m, aa;
	g = 1;
	if (d == '\"') {
		H(v);
		while (ch != '\"') {
			Y();
			*(char*)v++ = ch;
			o();
		}
		*(char*)v = 0;
		v = v + 4 & -4;
		o();
		ad();
	} else {
		aa = C;
		m = z;
		e = d;
		ad();
		if (e == 2) {
			H(m);
		} else if (aa == 2) {
			T(0);
			s(185, 0);
			if (e == '!')
				Z(m);
			else
				ae(m);
		} else if (e == '(') {
			w();
			ad();
		} else if (e == '*') {
			ad();
			e = d;
			ad();
			ad();
			if (d == '*') {
				ad();
				ad();
				ad();
				ad();
				e = 0;
			}
			ad();
			T(0);
			if (d == '=') {
				ad();
				ae(80);
				w();
				ae(89);
				ae(392 + (e == 0x100));
			} else if (e) {
				if (e == 0x100)
					ae(139);
				else
					ae(0xbe0f);
				q++;
			}
		} else if (e == '&') {
			N(10, *(int*)d); /* 10 == '\n' ? */
			ad();
		} else {
			g = *(int*)e;
			if (!g)
				g = dlsym(NULL, M);
			if (d == '=' & j) {
				ad();
				w();
				N(6, g);
			} else if (d != '(') {
				N(8, g);
				if (C == 11) {
					N(0, g);
					ae(z);
					ad();
				}
			}
		}
	}
	if (d == '(') {
		if (g == 1)
			ae(80);
		m = s(0xec81, 0);
		ad();
		j = 0;
		while (d != ')') {
			w();
			s(0x248489, j);
			if (d == ',')
				ad();
			j = j + 4;
		}
		*(int*)m = j;
		ad();
		if (!g) {
			e = e + 4;
			*(int*)e = s(0xe8, *(int*)e);
		} else if (g == 1) {
			s(0x2494ff, j);
			j = j + 4;
		} else {
			s(0xe8, g - q - 5);
		}
		if (j)
			s(0xc481, j);
	}
}

O(j)
{
	int e, g, m;
	if (j-- == 1)
		T(1);
	else {
		O(j);
		m = 0;
		while (j == C) {
			g = d;
			e = z;
			ad();
			if (j > 8) {
				m = S(e, m);
				O(j);
			} else {
				ae(80);
				O(j);
				ae(89);
				if (j == 4 | j == 5) {
					Z(e);
				} else {
					ae(e);
					if (g == '%') /* originally 37 */
						ae(146);
				}
			}
		}
		if (m && j > 8) {
			m = S(e, m);
			H(e ^ 1);
			B(5);
			A(m);
			H(e);
		}
	}
}

w()
{
	O(11);
}

U()
{
	w();
	return S(0, 0);
}

I(j)
{
	int m, g, e;
	if (d == 0x120) {
		ad();
		ad();
		m = U();
		ad();
		I(j);
		if (d == 0x138) {
			ad();
			g = B(0);
			A(m);
			I(j);
			A(g);
		} else {
			A(m);
		}
	} else if (d == 0x160 | d == 0x1f8) {
		e = d;
		ad();
		ad();
		if (e == 0x160) {
			g = q;
			m = U();
		} else {
			if (d != ';')
				w();
			ad();
			g = q;
			m = 0;
			if (d != ';')
				m = U();
			ad();
			if (d != ')') {
				e = B(0);
				w();
				B(g - q - 5);
				A(e);
				g = e + 4;
			}
		}
		ad();
		I(&m);
		B(g - q - 5);
		A(m);
	} else if (d == '{') {
		ad();
		ab(1);
		while (d != '}')
			I(j);
		ad();
	} else {
		if (d == 0x1c0) {
			ad();
			if (d != ';')
				w();
			K = B(K);
		} else if (d == 0x190) {
			ad();
			*(int*)j = B(*(int*)j);
		} else if (d != ';')
			w();
		ad();
	}
}

ab(j)
{
	int m;
	while (d == 0x100 | d != -1 & !j) {
		if (d == 0x100) {
			ad();
			while (d != ';') {
				if (j) {
					G = G + 4;
					*(int*)d = -G;
				} else {
					*(int*)d = v;
					v = v + 4;
				}
				ad();
				if (d == ',')
					ad();
			}
			ad();
		} else {
			A(*(int*)(d + 4));
			*(int*)d = q;
			ad();
			ad();
			m = 8;
			while (d != ')') {
				*(int*)d = m;
				m = m + 4;
				ad();
				if (d == ',')
					ad();
			}
			ad();
			K = G = 0;
			ae(0xe58955); /*more instructions? */
			m = s(0xec81, 0);
			I(0);
			A(K);
			ae(0xc3c9);
			*(int*)m = G;
		}
	}
}

main(int argc, char **argv)
{
	f = stdin;
	puts("what1\n");
	if (argc-- > 1) {
		argv++;
		f = fopen(*argv, "r");
	}
	puts("what2\n");
	D = strcpy(R = calloc(1, ALLOC_LEN),
		" int if else while break return for define main ")
		+ 48; /* length of string on upper line */
	puts("what3\n");
	v = calloc(1, ALLOC_LEN);
	q = ac = calloc(1, ALLOC_LEN);
	P = calloc(1, ALLOC_LEN);
	puts("what4\n");
	o();
	puts("what5\n");
	ad();
	puts("what6\n");
	ab(0);
	puts("what7\n");
	return (*(int (*)()) * (int*)(P + 592))(argc, argv);
}

