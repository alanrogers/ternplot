#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*** prototypes ***/
float u(float x, float y);
void beginplot(char *labx, char *laby, char *labz, float inches, FILE *ofp);
void endpicture(FILE *ofp);
void usage(void);


/*** externals ***/
float xcoeff=0.0;
float ycoeff=0.0;

/* horizontal position on triangular plot */
float u(float x, float y)
{
  if(xcoeff == 0.0)  /* set coefficients on first call */
  {
    xcoeff = 2.0/sqrt(3.0);
    ycoeff = 1.0/sqrt(3.0);
  }

  return(xcoeff*x + ycoeff*y);
}

/*  begin PicTeX plot */
void beginplot(char *labx, char *laby, char *labz, float inches, FILE *ofp)
{
  float sidelength;
  float offset = 4.0, xyoffset;

  xyoffset = offset/sqrt(2.0);

  sidelength = 2.0/sqrt(3.0);  // length of a side
  fputs(
"\\mbox{%\n"
"\\beginpicture\n", ofp);
  fprintf(ofp,
"\\setcoordinatesystem units <%fin, %fin>\n", inches, inches);
  fprintf(ofp,
"\\setplotarea x from 0 to %f, y from 0 to 1\n", sidelength);
  // bottom line
  fprintf(ofp,"\\plot 0 0 %f 0 /\n", sidelength);
  /* left line */
  fprintf(ofp,"\\plot 0 0 %f 1 /\n", u(0.0, 1.0));
  /* right line */
  fprintf(ofp,"\\plot %f 1 %f 0 /\n", u(0.0, 1.0), sidelength);
  /* label corners */
  fprintf(ofp,"\\put {%s} [lt] <%fpt,-%fpt> at %f 0\n", labx,
	  xyoffset, xyoffset, sidelength); 
  fprintf(ofp,"\\put {%s} [b] <0pt,%fpt> at %f 1\n", laby,
	  offset, sidelength/2.0); 
  fprintf(ofp,"\\put {%s} [rt] <-%fpt,-%fpt> at 0 0\n",
	  labz, xyoffset, xyoffset);
}

/* end PicTeX picture */
void endpicture(FILE *ofp) {
  fputs("\\endpicture}\n", ofp);
}

void usage(void) {
  fprintf(stderr,"Usage: triplot [options]\n");
  fprintf(stderr,"  where options may include:");
  fprintf(stderr,"  -x<xlabel>\n");
  fprintf(stderr,"  -y<ylabel>\n");
  fprintf(stderr,"  -z<zlabel>\n");
  fprintf(stderr,"  -i<plotsize in inches>\n\n");
  exit(1);
}

int main(int argc, char **argv) {
  int i;
  float inches = 2.0;  /* size of plot */
  float x, y;
  char xlab[30], ylab[30], zlab[30];
  FILE *ifp = stdin, *ofp = stdout;

  strcpy(xlab, "$X$");
  strcpy(ylab, "$Y$");
  strcpy(zlab, "$Z$");

  for(i=1; i<argc; i++)
  {
    if(argv[i][0] == '-')
    {
      switch(argv[i][1])
      {
      case 'x':
	strcpy(xlab, argv[i]+2);
	break;
      case 'y':
	strcpy(ylab, argv[i]+2);
	break;
      case 'z':
	strcpy(zlab, argv[i]+2);
	break;
      case 'i':
	inches = atof(argv[i]+2);
	break;
      default:
	usage();
      }
    }else
      usage();
  }
  beginplot(xlab, ylab, zlab, inches, ofp);
  fprintf(ofp,"\\multiput {.} at\n");
  while(fscanf(ifp,"%f%f", &x, &y) != EOF)
    fprintf(ofp, "  %f %f %% %f\n", u(x,y), y, x);
  fprintf(ofp,"/\n");
  endpicture(ofp);
  putc('\n', ofp);

  return 0;
}


  














