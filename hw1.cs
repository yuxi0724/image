using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            Bitmap image = new Bitmap(pictureBox1.Image);
            if (a.Checked)
            {
                Graphics graphics = pictureBox1.CreateGraphics();
                graphics.Clear(Color.Black);
                Rectangle pic = new Rectangle(0, 0, image.Width, image.Height);
                PointF center = new PointF(image.Width / 2, image.Height / 2);
                graphics.TranslateTransform(center.X, center.Y);
                graphics.RotateTransform(-trackBar1.Value*36);
                graphics.TranslateTransform(-center.X, -center.Y);
                graphics.DrawImage(image, pic);     
            }
            else if(b.Checked)
            {
                Image img = pictureBox1.Image;
                img=SetRoundPictureBox(img);
                Graphics graphics = pictureBox1.CreateGraphics();
                Rectangle pic = new Rectangle(0, 0, image.Width, image.Height);
                PointF center = new PointF(img.Width / 2, img.Height / 2);
               // graphics.TranslateTransform(center.X, center.Y); //改變中心位置 旋轉時會移動到   
                graphics.RotateTransform(-trackBar1.Value * 36);    //旋轉,有10格(故*36),逆時針(故*-1)
              //  graphics.TranslateTransform(-center.X, -center.Y);  //改回原本的中心位置
                graphics.DrawImage(img,0,0);    
            }
           
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void a_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }
        private Image SetRoundPictureBox(Image img) //切圖
        {
            //草圖
            Bitmap bitmap = new Bitmap(img.Width, img.Height);
            using (Graphics graphics = Graphics.FromImage(bitmap))
            {
                //讓圖片變得更光滑
                graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
                //設定開始切圓的位置及範圍
                Rectangle rect = new Rectangle(pictureBox1.Width/2-img.Height/2, 0, img.Height, img.Height);
                graphics.FillEllipse(new TextureBrush(img), rect);
              
            }
           return bitmap;
        }
    }
}
