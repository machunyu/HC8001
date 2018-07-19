//
//
//»­Ô²Ä£¿é C³ÌÐò
//
//////////////////////////////////
	
	
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
    
    
//====================================================================
//== image_set_pixel:
//== Sets a pixel passed in signed (x, y) coordinates, where (0,0) is at
//== the center of the image.
//=====================================================================  	
    	int
    	main (int argc, char *argv[])
    	{
    	  Image *image;    	
    	  image = image_new (600, 600);
		  
    	  image_fill  ( image , 0xff                 );
    	  draw_circle ( image , 200, 0x00,0x00,0xff  );
    	  image_save  ( image , "circle.ppm"         );    	
    	  image_free  ( image                        );
    	
    	  return 0;
    	}
	
	
//====================================================================
//== typedef struct: Image
//====================================================================
	    typedef struct {
          size_t         width   ;
          size_t         height  ;
          unsigned char  *data   ;
        } Image                  ;
//====================================================================
//== static Image : *image_new
//====================================================================
        static Image *image_new ( size_t width,
		                          size_t height
								)
		//-------
        {
          Image *image                                ;    
          image           =  malloc (sizeof *image)   ;
          image -> width  = width                     ;
            -> height = height                    ;
          image -> data   = malloc (width * height*3) ;
          return image                                ;
        }
		//-------
//====================================================================
//== image_set_pixel:
//====================================================================		
    
        static void
        image_free (Image *image)
        {
          free ( image -> data ) ;
          free ( image         ) ;
        }
//====================================================================
//== image_set_pixel:
//====================================================================    
        static void
        image_fill (Image *image , unsigned char value )
        {
           memset  (image->data  , value , image->width * image->height*3 ) ;
        }
    
//====================================================================
//== image_set_pixel:
//== Sets a pixel passed in signed (x, y) coordinates, where (0,0) is at
//== the center of the image.
//====================================================================
        static void
        image_set_pixel ( Image *image ,
                          ssize_t x    ,
                          ssize_t y    ,
           unsigned char  Rvalue       ,
           unsigned char  Gvalue       ,
           unsigned char  Bvalue       )
		//--------   
        {
           size_t         tx           ;
           size_t		  ty           ;
           unsigned char  *p           ;
    
           tx = ( image -> width  / 2 ) + x  ;
           ty = ( image -> height / 2 ) + y  ;
    
           p  = image -> data + ( ty * image -> width*3 ) + tx*3  ;
    
           *p     = Rvalue  ;
           *(p+1) = Gvalue  ;
           *(p+2) = Bvalue  ;
        }
		//-------
       
//====================================================================
//== static void: draw_circle
//== 
//=====================================================================
        static void
        draw_circle (    Image *image  ,
                 int           radius  ,
                 unsigned char Rvalue  ,
                 unsigned char Gvalue  ,
                 unsigned char Bvalue  )
        {
            int x                      ;
            int	y                      ;    
            for ( y = -radius ;   y <= radius; y++         )
            for ( x = -radius ;   x <= radius; x++         )
            if  ((x * x) + (y * y)  <= (radius * radius)   )  image_set_pixel ( image, x, y, Rvalue,Gvalue,Bvalue ) ;
        }
	
//====================================================================
//== static void : image_save
//== ( const Image *image ,const char  *filename )
//=====================================================================	
	
        static void
        image_save  ( const Image  *image    ,
                      const char   *filename 
				    )
        {
           FILE *out                                                        ;    
           out = fopen (filename, "wb" )                                    ;
           if (!out  )
           return                                                           ;
    
           fprintf (out, "P6\n"                                           ) ;
           fprintf (out, "%zu %zu\n", image->width,  image->height        ) ;
           fprintf (out, "255\n"                                          ) ;    
           fwrite  (image->data, 1  , image->width * image->height*3, out ) ;   
           fclose  (out                                                   ) ;
        }	
	
	
	

