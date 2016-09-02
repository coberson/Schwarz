//
//  schwarz.c
//  
//
//  Created by Chantal Oberson Ausoni on 14/09/2015.
//
// generating the meshes for the Schwarz lantern as well as the corresponding 2D origami pattern
// both meshes for use with program medit (Prof. Pascal Frey)

#include "schwarz.h"

int main(int argc, char* argv[])
{
    
    FILE* fmesh;
    FILE* fsol;
    
    int n=20;
    int m=9;
    int nv,ne,nf;
    int i,j,v;
    
    double h;
    double alpha;
    
    double x,y,z;
    
    if (argc==3)
    {
        if(sscanf(argv[1],"%d", &n) !=1)
        {
            printf("Integer awaited");
                exit(EXIT_FAILURE);
        }
        if(sscanf(argv[2],"%d", &m) !=1)
        {
            printf("Integer awaited");
            exit(EXIT_FAILURE);
        }
    }
    
    printf("Made schwarz lantern with parameters n=%d m=%d \n", n,m);
    
    
    h = 1/(double) m;
    alpha = 2*M_PI/n;
    
    printf("Height of one step %f; Angle for one triangle %f\n", h,alpha);
    
    nv = n*(m+1);
    nf = 2*nv;
    if (m % 2 ==1) nf = nf - n;
    
     printf("Number of vertices %d; Number of triangles %d\n", nv,nf);
    
    
    
    
    fmesh=fopen("lantern.mesh","w");
    fsol=fopen("lantern.sol","w");
    fprintf (fmesh,"MeshVersionFormatted 2\n Dimension\n\t3\n Vertices\n\t%d\n", nv);
    fprintf (fsol,"MeshVersionFormatted 2\n Dimension\n\t3\n SolAtVertices\n\t%d\n 1 1\n", nv);
    for (j=0; j<= m/2-1; j++)
    {
        for (i=0; i< n; i++)
        {
            x=cos(i*alpha);
            y=sin(i*alpha);
            z=2*j*h;
            fprintf(fmesh,"%f\t%f\t%f\t1\n", x, y, z);
            fprintf(fsol,"%f\n",z);
            
        }
        
        for (i=0; i< n; i++)
        {
            x=cos((i+0.5)*alpha);
            y=sin((i+0.5)*alpha);
            z=(2*j+1)*h;
            fprintf(fmesh,"%f\t%f\t%f\t1\n", x, y, z);
            fprintf(fsol,"%f\n",z);
        }
    }
    
    j = m/2;
    
    for (i=0; i< n; i++)
    {
        //printf("%d\t%d\n", i,j);
        x=cos(i*alpha);
        y=sin(i*alpha);
        z=2*j*h;
        fprintf(fmesh,"%f\t%f\t%f\t1\n", x, y, z);
        fprintf(fsol,"%f\n",z);
    }

    
    if (m % 2 ==1)
    {
        for (i=0; i< n; i++)
        {
            x=cos((i+0.5)*alpha);
            y=sin((i+0.5)*alpha);
            z=(2*j+1)*h;
            fprintf(fmesh,"%f\t%f\t%f\t1\n", x, y, z);
            fprintf(fsol,"%f\n",z);
        }

    }
    
    fprintf (fmesh,"Triangles\n\t%d\n", nf);
    
    for (j=0; j<= m/2-1; j++)
    {
        //printf("%d\t%d\n", 2*j,2*j+1);
        for (i=0; i< n-1; i++)
        {
            fprintf(fmesh,"%d\t%d\t%d\t1\n",2*j*n+i+1,2*j*n+i+2,(2*j+1)*n+i+1);
            fprintf(fsol,"%d\n",2*j);
            fprintf(fmesh,"%d\t%d\t%d\t2\n",2*j*n+(i+1)+1,(2*j+1)*n+(i+1)+1,(2*j+1)*n+i+1);
            //fprintf(fsol,"%d\n",2*j+1);
        }
        i = n-1;
        fprintf(fmesh,"%d\t%d\t%d\t1\n",2*j*n+i+1,2*j*n+1,(2*j+1)*n+i+1);
        fprintf(fsol,"%d\n",2*j);
        fprintf(fmesh,"%d\t%d\t%d\t2\n",2*j*n+1,(2*j+1)*n+i+1,(2*j+1)*n+1);
        //fprintf(fsol,"%d\n",2*j+1);
        for (i=0; i< n-1; i++)
        {
            fprintf(fmesh,"%d\t%d\t%d\t1\n",(2*j+1)*n+i+1,(2*j+1)*n+i+2,(2*j+2)*n+i+2);
            fprintf(fsol,"%d\n",2*j+1);
            fprintf(fmesh,"%d\t%d\t%d\t2\n",(2*j+1)*n+(i+1),(2*j+2)*n+(i+1)+1,(2*j+2)*n+i+1);
            //fprintf(fsol,"%d\n",2*j+2);
        }
        i = n-1;
        fprintf(fmesh,"%d\t%d\t%d\t1\n",(2*j+1)*n+i+1,(2*j+1)*n+1,(2*j+1)*n+i+2);
        fprintf(fsol,"%d\n",2*j+1);
        fprintf(fmesh,"%d\t%d\t%d\t2\n",(2*j+1)*n+i+1,(2*j+1)*n+i+2,(2*j+2)*n+i+1);
        //fprintf(fsol,"%d\n",2*j+2);
        
    }
    
    if (m % 2 ==1)
    {
        j=m/2;
        for (i=0; i< n-1; i++)
        {
            fprintf(fmesh,"%d\t%d\t%d\t1\n",2*j*n+i+1,2*j*n+i+2,(2*j+1)*n+i+1);
            fprintf(fsol,"%d\n",2*j);
            fprintf(fmesh,"%d\t%d\t%d\t2\n",2*j*n+(i+1)+1,(2*j+1)*n+(i+1)+1,(2*j+1)*n+i+1);
            //fprintf(fsol,"%d\n",2*j+1);
        }
        i = n-1;
        fprintf(fmesh,"%d\t%d\t%d\t1\n",2*j*n+i+1,2*j*n+1,(2*j+1)*n+i+1);
        fprintf(fsol,"%d\n",2*j);
        fprintf(fmesh,"%d\t%d\t%d\t2\n",2*j*n+1,(2*j+1)*n+i+1,(2*j+1)*n+1);
        //fprintf(fsol,"%d\n",2*j+1);

    }

    fclose(fmesh);
    fclose(fsol);

    
    fmesh=fopen("origami.mesh","w");
    fprintf (fmesh,"MeshVersionFormatted 2\n Dimension\n\t2\n Vertices\n\t%d\n", (n+1)*(m+1)+(m+1)/2);
    fsol=fopen("origami.sol","w");
    fprintf (fsol,"MeshVersionFormatted 2\n Dimension\n\t2\n SolAtEdges\n\t%d\n 1 1\n", 3*m*(2*n+1));
    
    alpha = 1/(double)n;
    
    for (j=0; j<= m; j++)
    {
        if (j%2==0)
        {
            for (i=0; i< n; i++) fprintf(fmesh,"%f\t%f\t1\n", i*alpha, j*h);
            fprintf(fmesh,"%f\t%f\t1\n", 1.,j*h);
        }
        else
        {
            fprintf(fmesh,"%f\t%f\t1\n", 0.,j*h);
            for (i=0; i< n; i++) fprintf(fmesh,"%f\t%f\t1\n", (i+0.5)*alpha, j*h);
            fprintf(fmesh,"%f\t%f\t1\n", 1.,j*h);
        }
        
    }
    
    fprintf (fmesh,"Triangles\n\t%d\n", m*(2*n+1));
    
    for (j=0; j< m; j++)
    {
        if (j%2==0)
        {
            v=(j/2)*(2*n+3);
            fprintf(fmesh,"%d\t%d\t%d\t1\n",v+1,v+n+3,v+n+2);
            for (i=0; i< n; i++) fprintf(fmesh,"%d\t%d\t%d\t1\n",v+i+1,v+i+2,v+i+n+3);
            for (i=1; i<= n; i++) fprintf(fmesh,"%d\t%d\t%d\t1\n",v+i+1,v+i+n+3,v+i+n+2);
            //fprintf(fmesh,"%d\t%d\t%d\t1\n",v+n+1,v+2*n+2,v+2*n+3);
        }
        else
        {
           v=((j-1)/2)*(2*n+3)+n+1;
           for (i=0; i< n; i++) fprintf(fmesh,"%d\t%d\t%d\t1\n",v+i+1,v+i+2,v+i+2+n+1);
           for (i=1; i<= n; i++) fprintf(fmesh,"%d\t%d\t%d\t1\n",v+i+1,v+i+n+3,v+i+n+2);
           fprintf(fmesh,"%d\t%d\t%d\t1\n",v+n+1,v+n+2,v+2*n+3);
        }
        
    }
    
    fprintf (fmesh,"Edges\n\t%d\n", 3*m*(2*n+1));//corriger!
    
    for (j=0; j< m; j++)
    {
        if (j%2==0)
        {
            v=(j/2)*(2*n+3);
            fprintf(fmesh,"%d\t%d\t1\n",v+1,v+n+3);
            fprintf(fsol,"%f\n",1.);
            fprintf(fmesh,"%d\t%d\t1\n",v+1,v+n+2);
             fprintf(fsol,"%f\n",1.);
            fprintf(fmesh,"%d\t%d\t6\n",v+n+2,v+n+3);
             fprintf(fsol,"%f\n",2.);
            for (i=0; i< n; i++)
            {
                fprintf(fmesh,"%d\t%d\t6\n",v+i+1,v+i+2);
                 fprintf(fsol,"%f\n",2.);
                fprintf(fmesh,"%d\t%d\t1\n",v+i+1,v+i+n+3);
                 fprintf(fsol,"%f\n",1.);
                fprintf(fmesh,"%d\t%d\t1\n",v+i+2,v+i+n+3);
                 fprintf(fsol,"%f\n",1.);
                
            }
            for (i=1; i<= n; i++)
            {
                fprintf(fmesh,"%d\t%d\t1\n",v+i+1,v+i+n+3);
                 fprintf(fsol,"%f\n",1.);
                fprintf(fmesh,"%d\t%d\t1\n",v+i+1,v+i+n+2);
                 fprintf(fsol,"%f\n",1.);
                fprintf(fmesh,"%d\t%d\t6\n",v+i+n+2,v+i+n+3);
                 fprintf(fsol,"%f\n",2.);
            }
            
            //fprintf(fmesh,"%d\t%d\t%d\t1\n",v+n+1,v+2*n+2,v+2*n+3);
        }
        else
        {
            v=((j-1)/2)*(2*n+3)+n+1;
            for (i=0; i< n; i++)
            {
                fprintf(fmesh,"%d\t%d\t6\n",v+i+1,v+i+2);
                 fprintf(fsol,"%f\n",2.);
                fprintf(fmesh,"%d\t%d\t1\n",v+i+1,v+i+n+3);
                 fprintf(fsol,"%f\n",1.);
                fprintf(fmesh,"%d\t%d\t1\n",v+i+2,v+i+n+3);
                 fprintf(fsol,"%f\n",1.);
                
            }
            for (i=1; i<= n; i++)
            {
                fprintf(fmesh,"%d\t%d\t1\n",v+i+1,v+i+n+3);
                 fprintf(fsol,"%f\n",1.);
                fprintf(fmesh,"%d\t%d\t1\n",v+i+1,v+i+n+2);
                 fprintf(fsol,"%f\n",1.);
                fprintf(fmesh,"%d\t%d\t6\n",v+i+n+2,v+i+n+3);
                 fprintf(fsol,"%f\n",2.);
            }

            fprintf(fmesh,"%d\t%d\t6\n",v+n+1,v+n+2);
             fprintf(fsol,"%f\n",2.);
            fprintf(fmesh,"%d\t%d\t1\n",v+n+1,v+2*n+3);
             fprintf(fsol,"%f\n",1.);
            fprintf(fmesh,"%d\t%d\t1\n",v+n+2,v+2*n+3);
             fprintf(fsol,"%f\n",1.);
        }
        
    }
    fprintf(fsol,"End\n");

    fclose(fmesh);
    fclose(fsol);
}