/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package differential_with_runlength_encodeing;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author esraa
 */
public class Differential_With_RunLength_Encodeing {

    /**
     * @param args the command line arguments
     */
  
    public static void main(String[] args) throws FileNotFoundException, IOException {
        // TODO code application logic here
 //---------------------------Encoding---------------------------------------------------
         FileReader fileReader = new FileReader("file.txt");
         BufferedReader bufferedReader =new BufferedReader(fileReader);
         String line;
          String encodedString="";
         while((line = bufferedReader.readLine()) != null) 
            {
              encodedString+=DE_Encoding(line);
              encodedString+=",";
            }
        if((encodedString.charAt(encodedString.length()-1))==',')//h4el a5er ','
        {
            encodedString=encodedString.substring(0,encodedString.length()-1);
        }    
        System.out.println("enco="+encodedString);
 //---------------------------Decoding------------------------------------------------
         String fileName="file2.txt";
        DE_Decoding(encodedString,fileName);//hyktb f file
        
  
    }
    
 //===================================DE===================================================================
 //---------------------------------------DE_Encoding-----------------------------------------------------------
    static String DE_Encoding(String line)//hydecode line
    {
        String encodedString="";
        try
           {
           
               String encodedStringTemp="";
                 String arr[]= line.split(" ");
              
               for(int i=0;i<arr.length;i++)
               {
                   if(i==0)
                   {
                      encodedStringTemp+=arr[i];
                      encodedStringTemp+=",";  
                   }
                   else
                   {
                    int difference=(Integer.parseInt(arr[i])-Integer.parseInt(arr[i-1]));
                    encodedStringTemp+=Integer.toString(difference);
                    encodedStringTemp+=",";
                   }
                 
               }
              
               String []t=encodedStringTemp.split(",");
                ArrayList <String>output=DE_RLE_Encoding(t);
                for(int y=0;y<output.size();y++)
                {
               
                    encodedString+=output.get(y);
                    encodedString+=",";
                }
              
             
        }
        catch(Exception e)
        {
            System.out.println("Error open file");
        }
        
        
        if((encodedString.charAt(encodedString.length()-1))==',')//h4el a5er ','
        {
            encodedString=encodedString.substring(0,encodedString.length()-1);
        }
      
        return encodedString;
    }

  //---------------------------------------------------DE_Decoding-----------------------------------------------------------------
    
    static void DE_Decoding(String encodedString,String fileName) throws FileNotFoundException, IOException
    {
        int lineWidth=5;//to change
        File fout = new File(fileName);
	FileOutputStream fos = new FileOutputStream(fout);
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));
        ArrayList <String>decoded=new ArrayList<String>();
        String[] en=encodedString.split(",");
       for(int i=0;i<en.length;i++)
       {
           int depth=DE_RLE_Decoding(decoded,lineWidth,en[i],bw);//HYB3T index index w hnak hy7oto fl dile bb3d ma ygeb kmto
       }
      bw.close();
    }
    
 //---------------------------------------------RLE_Encoding-----------------------------------------------------------------------
    static  ArrayList <String> DE_RLE_Encoding(String []src)
    {
       ArrayList <String>encodedSrc=new ArrayList<String>();
       for(int i=0;i<src.length;i++)
       {
           int depth=1;
           if(i<src.length-1)
           {
               for(int j=i+1;j<src.length;j++)
                {
                    if(src[i].equals(src[j]))
                    {
                        depth++;
                    }
                    else 
                    {
                        break;
                    }
                }
               if(depth>=4)
               { 
                   //lw atkrr aktr mn 9 mrat h2smhm 3la kza mara
                   if(depth<=9)
                   {
                       String h="";
                       h+=src[i];
                       h+="!";
                       h+=Integer.toString(depth);
                       encodedSrc.add(h);
                       i=(i+depth)-1;
                   }
                   else
                   {
                        if(depth>=9)
                           {   String h="";
                               h+=src[i];
                               h+="!";
                               h+="9";
                               encodedSrc.add(h);
                                depth=depth-9;
                           }
                          
                         i=(i+9)-1;
                       }
               }
               else
               {
                    String h="";
                    h+=src[i];
                    encodedSrc.add(h);
               }
               
           }
           else
           {
                    String h="";
                    h+=src[i];
                    encodedSrc.add(h);
           }
     
       }
        return encodedSrc;
    }
 //-------------------------------------------------------DE_RLE_Decoding---------------------------------------------------------------------
    
    static int  DE_RLE_Decoding(ArrayList <String>decoded,int lineWidth,String encodedSrc,BufferedWriter bw) throws IOException
    {
       // ArrayList <String>decodedSrc=new ArrayList<String>();
        
           int depth=0;
               if(encodedSrc.contains("!"))
                {
                    depth=Integer.parseInt(encodedSrc.substring(2,3));
                   for(int j=0;j<depth;j++)
                   {
                      decoded.add(encodedSrc.substring(0,1));
                      bw.write(encodedSrc.substring(0,1));
                      bw.write(" ");
                     
                   }
                  
                }
                else
                {
                    if(decoded.size()%lineWidth==0)
                    {
                        decoded.add(encodedSrc);
                        bw.write(encodedSrc);
                        bw.write(" ");
                    }
                    else
                    {
                    String r=Integer.toString(Integer.parseInt(encodedSrc)+Integer.parseInt(decoded.get(decoded.size()-1)));
                    decoded.add(r);
                     bw.write(r);
                     bw.write(" ");
                    }
                }
               if(decoded.size()%lineWidth==0)
               {
                   bw.newLine();
               }
               return depth;
  }
           
}
  
