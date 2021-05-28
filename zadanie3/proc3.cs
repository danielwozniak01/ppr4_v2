using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Diagnostics;
using System.ComponentModel;



namespace socket
{

    class Program
    {
        static void Main(string[] args)
        {
            byte[] bytes = new Byte[4096];
            string data = null;
            IPEndPoint localEndPoint = new IPEndPoint(IPAddress.Any, 12345);
            Socket listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                listener.Bind(localEndPoint);
                listener.Listen(10);

                while (true)
                {
                    try
                    {
                        Console.WriteLine("Waiting for a connection...");
                        Socket handler = listener.Accept();
                        for (int i = 0; i < bytes.Length; i++)
                        {
                            bytes[i] = 0;
                        }
                        handler.Receive(bytes);
                        data = System.Text.Encoding.UTF8.GetString(bytes);
                        int index = data.IndexOf('\0');
                        if (index >= 0)
                            data = data.Remove(index);
                        handler.Shutdown(SocketShutdown.Both);
                        handler.Close();
                        Console.WriteLine(data);
                        bytes = Encoding.Default.GetBytes(data);
                        string hexString = BitConverter.ToString(bytes);
                        hexString = hexString.Replace("-", "");
                        Console.WriteLine(hexString);

                    }
                    catch (Exception e)
                    {
                        Console.WriteLine(e.ToString());
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }

            Console.WriteLine("\nPress ENTER to continue...");
            Console.Read();
        }
    }
}
