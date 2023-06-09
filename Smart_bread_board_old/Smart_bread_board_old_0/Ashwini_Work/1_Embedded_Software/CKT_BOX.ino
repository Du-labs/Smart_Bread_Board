//------------------------------------ From Somu ----------------------------------------------------
#define OC1 A0
#define OC2 A1
#define OC3 A2
#define OC4 A3
#define OC5 A4
#define OC6 A5
/////////////definingall data pins (D0-D7 pins///////////////
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define IN5 6
#define IN6 7
#define IN7 8
#define IN8 9
//int Relay_no ;
int one_loop = 0;
//---------------------------------------------------------------------------------------------------
// Declare 4 nodes
String Node_1, Node_2, Node_3, Node_4;

// Declare 6*2 component port
String A_1, A_2, B_1, B_2, C_1, C_2, D_1, D_2, E_1, E_2, F_1, F_2;
char Comp1[40], Comp2[40], Comp3[40], Comp4[40], Comp5[40], Comp6[40];

int trim_index = 0;
// Declare array of relays
int Relay[48];

// Trimmed data
char Trim_data[250];
// Raw data
char Raw_data[250];
//
int i = 0;
int One_loop = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                                          // initialize serial:
  Serial.println("Arduino bravo");

  //------------------------------------ From Somu ----------------------------------------------------
  pinMode(OC1, OUTPUT);
  pinMode(OC2, OUTPUT);
  pinMode(OC3, OUTPUT);
  pinMode(OC4, OUTPUT);
  pinMode(OC5, OUTPUT);
  pinMode(OC6, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);

  digitalWrite(OC1, HIGH); // follow data when high, when low set latch
  digitalWrite(OC2, HIGH);
  digitalWrite(OC3, HIGH);
  digitalWrite(OC4, HIGH);
  digitalWrite(OC5, HIGH);
  digitalWrite(OC6, HIGH);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, HIGH);
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, HIGH);
  //---------------------------------------------------------------------------------------
}

int relay_max = 48, count_relay = 0;

void loop() {

  //--------------------------------------------------------------------------------------------------------------------------------------------
  // Recieve raw data from serial port

  do
  {
    if (Serial.available() > 0)
    {
      Raw_data[i] = Serial.read();                                        // Read all characters and store in array
      //Serial.print(Raw_data[i]);
      i++;
    }
  } while (Raw_data[i - 1] != '#'); // End of characters

  // ["V",["10,-5","GND"]]
  // ["R",["10,-5","15,-5"]]
  // ["C",["15,-5","GND"]]
  // ["R",["15,-10","GND"]]
  // ["D",["10,-5","15,-10"],0.000001]
  //--------------------------------------------------------------------------------------------------------------------------------------------
  // Trim garbage values
  int j = 0;
  int count = 0;
  // Serial.print("i = ");
  // Serial.println(i);
  if (One_loop == 0)
  {
    One_loop = 1;
    while (j < i)
    {
      if (Raw_data[j] == '[' || Raw_data[j] == ']')
      {
        j++;
      }
      else
      {
        Trim_data[j] = Raw_data[j];
        //Serial.print(Trim_data[j]);
        trim_index++;
        j++;
      }
    } //while (j < i)
    Serial.println("Second Trim");
    // ----------------------------------------------------------------------------------------------------------------------------------------------------
    // Store each component co-ordinates.
    j = 0;
    int k = 0;
    while (j < i)
    {
      //Serial.print("j = ");
      //Serial.println(j);
      Serial.print("Comp1:");
      while ((Trim_data[j] != ' ') && (j < i))
      {
        Comp1[k] = Trim_data[j];
        // Serial.print(Comp1[k]);
        k++;
        j++;
      }

      j++;
      k = 0;
      Serial.println(" ");
      //Serial.print("j = ");
      //Serial.println(j);
      Serial.print("Comp2:");
      while ((Trim_data[j] != ' ') && (j < i))
      {
        Comp2[k] = Trim_data[j];
        //  Serial.print(Comp2[k]);
        k++;
        j++;
      }

      j++;
      k = 0;
      Serial.println(" ");
      //Serial.print("j = ");
      //Serial.println(j);
      Serial.print("Comp3:");
      while ((Trim_data[j] != ' ') && (j < i))
      {
        Comp3[k] = Trim_data[j];
        //   Serial.print(Comp3[k]);
        k++;
        j++;
      }

      j++;
      k = 0;
      Serial.println(" ");
      Serial.print("Comp4:");
      //Serial.print("j = ");
      //Serial.println(j);
      while ((Trim_data[j] != ' ') && (j < i))
      {
        Comp4[k] = Trim_data[j];
        //     Serial.print(Comp4[k]);
        k++;
        j++;
      }

      j++;
      k = 0;
      Serial.println(" ");
      Serial.print("Comp5:");
      //Serial.print("j = ");
      //Serial.println(j);
      while ((Trim_data[j] != ' ') && (j < i))
      {
        Comp5[k] = Trim_data[j];
        //    Serial.print(Comp5[k]);
        k++;
        j++;
      }

      j++;
      k = 0;
      Serial.println(" ");
      Serial.print("Comp6:");
      //Serial.print("j = ");
      //Serial.println(j);
      while ((Trim_data[j] != ' ') && (j < i))
      {
        Comp6[k] = Trim_data[j];
        //    Serial.print(Comp6[k]);
        k++;
        j++;
      }
    } //while (j < i)

    /* Comp1: "V", "-15,-14","-15,-8"  
      Comp2: "R", "-11,-2","-6,-2"  
      Comp3: "T", "3,-14","3,-8"  
      Comp4: "C", "15,-1","20,-1"  
      Comp5: "D", "19,-12","24,-12" ,null 
      Comp6: "NPN", "30,-16","34,-18","34,-14"  # */
    //------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Get and store co-ordinates for each point of component and assign nodes.
    int colon_count = 0;
    Serial.println("Third trimming");

    // --------------------------A-----------------------------------------
    j = 0;
    while (colon_count < 3)
    {
      if (Comp1[j] == '"')
      {
        colon_count++;
      }
      j++;
    }

    do
    {
      A_1 += Comp1[j];
      j++;
    } while (Comp1[j] != '"');
    Serial.println("");
    // ------ A2
    j = 0;
    colon_count = 0;

    while (colon_count < 5)
    {
      if (Comp1[j] == '"')
      {
        // Serial.println(Comp2[j]);
        colon_count++;
      }
      j++;
    }
    // Serial.print("A_2_array: ");
    do
    {
      A_2 += Comp1[j];
      j++;
    } while (Comp1[j] != '"');

    Serial.println(A_1);
    Serial.println(A_2);
    // ------------------------------B-------------------------------------
    colon_count = 0;
    j = 0;
    while (colon_count < 3)
    {
      if (Comp2[j] == '"')
      {
        colon_count++;
      }
      j++;
    }

    do
    {
      B_1 += Comp2[j];
      j++;
    } while (Comp2[j] != '"');
    Serial.println("");
    // ------ B2
    j = 0;
    colon_count = 0;

    while (colon_count < 5)
    {
      if (Comp2[j] == '"')
      {
        // Serial.println(Comp2[j]);
        colon_count++;
      }
      j++;
    }

    do
    {
      B_2 += Comp2[j];
      j++;
    } while (Comp2[j] != '"');

    Serial.println(B_1);
    Serial.println(B_2);

    // ------------------------------C-------------------------------------
    colon_count = 0;
    j = 0;
    while (colon_count < 3)
    {
      if (Comp3[j] == '"')
      {
        colon_count++;
      }
      j++;
    }

    do
    {
      C_1 += Comp3[j];
      j++;
    } while (Comp3[j] != '"');
    Serial.println("");
    // ------ C2
    j = 0;
    colon_count = 0;

    while (colon_count < 5)
    {
      if (Comp3[j] == '"')
      {
        colon_count++;
      }
      j++;
    }

    do
    {
      C_2 += Comp3[j];
      j++;
    } while (Comp3[j] != '"');

    Serial.println(C_1);
    Serial.println(C_2);
    // ------------------------------D-------------------------------------

    colon_count = 0;
    j = 0;
    while (colon_count < 3)
    {
      if (Comp4[j] == '"')
      {
        colon_count++;
      }
      j++;
    }

    do
    {
      D_1 += Comp4[j];
      j++;
    } while (Comp4[j] != '"');
    Serial.println("");
    // ------ C2
    j = 0;
    colon_count = 0;

    while (colon_count < 5)
    {
      if (Comp4[j] == '"')
      {
        colon_count++;
      }
      j++;
    }

    do
    {
      D_2 += Comp4[j];
      j++;
    } while (Comp4[j] != '"');

    Serial.println(D_1);
    Serial.println(D_2);

    // ------------------------------E-------------------------------------

    colon_count = 0;
    j = 0;
    while (colon_count < 3)
    {
      if (Comp5[j] == '"')
      {
        colon_count++;
      }
      j++;
    }

    do
    {
      E_1 += Comp5[j];
      j++;
    } while (Comp5[j] != '"');
    Serial.println("");
    // ------ E2
    j = 0;
    colon_count = 0;

    while (colon_count < 5)
    {
      if (Comp5[j] == '"')
      {
        colon_count++;
      }
      j++;
    }

    do
    {
      E_2 += Comp5[j];
      j++;
    } while (Comp5[j] != '"');

    Serial.println(E_1);
    Serial.println(E_2);

    // ------------------------------F-------------------------------------

    colon_count = 0;
    j = 0;
    while (colon_count < 3)
    {
      if (Comp6[j] == '"')
      {
        colon_count++;
      }
      j++;
    }

    do
    {
      F_1 += Comp6[j];
      j++;
    } while (Comp6[j] != '"');
    Serial.println("");
    // ------ F2
    j = 0;
    colon_count = 0;

    while (colon_count < 5)
    {
      if (Comp6[j] == '"')
      {
        colon_count++;
      }
      j++;
    }

    do
    {
      F_2 += Comp6[j];
      j++;
    } while (Comp6[j] != '"');

    Serial.println(F_1);
    Serial.println(F_2);

    // Output from this level
    /*
      -77,-40
      -72,-40

      -8,-9
      -3,-9

      -3,-9
      3,-9

      3,-9
      8,-9

      3,-9
      8,-9

      3,-9
      8,-9 */

    //--------------------------------- Assign nodes--------------------------------------------------------------------------------------------------------------------
    // Assign first 2 nodes
    Node_1 = A_1;
    Node_2 = A_2;
    Node_3 = "";
    Node_4 = "";
    // ---------------------------------------- Node 3 --------------------------------------------------------
    if (B_1 != Node_1 && B_1 != Node_2 && B_1 != Node_3 && B_1 != Node_4)  // Look for unique node
    {
      Node_3 = B_1;  // New node
    }

    if (B_2 != Node_1 && B_2 != Node_2 && B_2 != Node_3 && B_2 != Node_4)  // Look for unique node
    {
      Node_3 = B_2;  // New node
    }

    if (C_1 != Node_1 && C_1 != Node_2 && C_1 != Node_3 && C_1 != Node_4)  // Look for unique node
    {
      Node_3 = C_1;  // New node
    }

    if (C_2 != Node_1 && C_2 != Node_2 && C_2 != Node_3 && C_2 != Node_4)  // Look for unique node
    {
      Node_3 = C_2;  // New node
    }

    if (D_1 != Node_1 && D_1 != Node_2 && D_1 != Node_3 && D_1 != Node_4)  // Look for unique node
    {
      Node_3 = D_1;  // New node
    }

    if (D_2 != Node_1 && D_2 != Node_2 && D_2 != Node_3 && D_2 != Node_4)  // Look for unique node
    {
      Node_3 = D_2;  // New node
    }

    if (E_1 != Node_1 && E_1 != Node_2 && E_1 != Node_3 && E_1 != Node_4)  // Look for unique node
    {
      Node_3 = E_1;  // New node
    }

    if (E_2 != Node_1 && E_2 != Node_2 && E_2 != Node_3 && E_2 != Node_4)  // Look for unique node
    {
      Node_3 = E_2;  // New node
    }

    if (F_1 != Node_1 && F_1 != Node_2 && F_1 != Node_3 && F_1 != Node_4)  // Look for unique node
    {
      Node_3 = F_1;  // New node
    }

    if (F_2 != Node_1 && F_2 != Node_2 && F_2 != Node_3 && F_2 != Node_4)  // Look for unique node
    {
      Node_3 = F_2;  // New node
    }

    // ---------------------------------------- Node 4 --------------------------------------------------------
    if (B_1 != Node_1 && B_1 != Node_2 && B_1 != Node_3 && B_1 != Node_4)  // Look for unique node
    {
      Node_4 = B_1;  // New node
    }

    if (B_2 != Node_1 && B_2 != Node_2 && B_2 != Node_3 && B_2 != Node_4)  // Look for unique node
    {
      Node_4 = B_2;  // New node
    }

    if (C_1 != Node_1 && C_1 != Node_2 && C_1 != Node_3 && C_1 != Node_4)  // Look for unique node
    {
      Node_4 = C_1;  // New node
    }

    if (C_2 != Node_1 && C_2 != Node_2 && C_2 != Node_3 && C_2 != Node_4)  // Look for unique node
    {
      Node_4 = C_2;  // New node
    }

    if (D_1 != Node_1 && D_1 != Node_2 && D_1 != Node_3 && D_1 != Node_4)  // Look for unique node
    {
      Node_4 = D_1;  // New node
    }

    if (D_2 != Node_1 && D_2 != Node_2 && D_2 != Node_3 && D_2 != Node_4)  // Look for unique node
    {
      Node_4 = D_2;  // New node
    }

    if (E_1 != Node_1 && E_1 != Node_2 && E_1 != Node_3 && E_1 != Node_4)  // Look for unique node
    {
      Node_4 = E_1;  // New node
    }

    if (E_2 != Node_1 && E_2 != Node_2 && E_2 != Node_3 && E_2 != Node_4)  // Look for unique node
    {
      Node_4 = E_2;  // New node
    }

    if (F_1 != Node_1 && F_1 != Node_2 && F_1 != Node_3 && F_1 != Node_4)  // Look for unique node
    {
      Node_4 = F_1;  // New node
    }

    if (F_2 != Node_1 && F_2 != Node_2 && F_2 != Node_3 && F_2 != Node_4)  // Look for unique node
    {
      Node_4 = F_2;  // New node
    }

    Serial.println("");
    Serial.print("Node_1: ");
    Serial.println(Node_1);
    Serial.print("Node_2: ");
    Serial.println(Node_2);
    Serial.print("Node_3: ");
    Serial.println(Node_3);
    Serial.print("Node_4: ");
    Serial.println(Node_4);
    /*-8,-4
      -3,-9

      -3,-9
      3,-4

      -8,-4
      -2,-4

      -2,-4
      3,-4

      -2,-4
      3,-4

      -2,-4
      3,-4
      -8,-4
      -3,-9
      3,-4
      -2,-4 */
    //---------------------------------------------- Activate relays ----------------------------------------------------

    //------------------------------------------ A1 ---------------------------------------
    if (A_1 == Node_1)
    {
      Relay[0] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (A_1 == Node_2)
    {
      Relay[1] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }
    if (A_1 == Node_3)
    {
      Relay[2] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (A_1 == Node_4)
    {
      Relay[3] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }

    //------------------------------------------ A2 ---------------------------------------
    if (A_2 == Node_1)
    {
      Relay[4] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (A_2 == Node_2)
    {
      Relay[5] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }
    if (A_2 == Node_3)
    {
      Relay[6] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (A_2 == Node_4)
    {
      Relay[7] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }

    //------------------------------------------ B1 ---------------------------------------
    if (B_1 == Node_1)
    {
      Relay[8] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (B_1 == Node_2)
    {
      Relay[9] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }
    if (B_1 == Node_3)
    {
      Relay[10] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (B_1 == Node_4)
    {
      Relay[11] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }

    //------------------------------------------ B2 ---------------------------------------
    if (B_2 == Node_1)
    {
      Relay[12] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (B_2 == Node_2)
    {
      Relay[13] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }
    if (B_2 == Node_3)
    {
      Relay[14] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (B_2 == Node_4)
    {
      Relay[15] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }


    //------------------------------------------ C1 ---------------------------------------
    if (C_1 == Node_1)
    {
      Relay[16] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (C_1 == Node_2)
    {
      Relay[17] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }
    if (C_1 == Node_3)
    {
      Relay[18] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (C_1 == Node_4)
    {
      Relay[19] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }

    //------------------------------------------ C2 ---------------------------------------
    if (C_2 == Node_1)
    {
      Relay[20] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (C_2 == Node_2)
    {
      Relay[21] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }
    if (C_2 == Node_3)
    {
      Relay[22] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (C_2 == Node_4)
    {
      Relay[23] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }

    //------------------------------------------ D1 ---------------------------------------
    if (D_1 == Node_1)
    {
      Relay[24] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (D_1 == Node_2)
    {
      Relay[25] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }
    if (D_1 == Node_3)
    {
      Relay[26] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (D_1 == Node_4)
    {
      Relay[27] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }

    //------------------------------------------ D2 ---------------------------------------
    if (D_2 == Node_1)
    {
      Relay[28] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (D_2 == Node_2)
    {
      Relay[29] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }
    if (D_2 == Node_3)
    {
      Relay[30] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (D_2 == Node_4)
    {
      Relay[31] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }

    //------------------------------------------ E1 ---------------------------------------
    if (E_1 == Node_1)
    {
      Relay[32] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (E_1 == Node_2)
    {
      Relay[33] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }
    if (E_1 == Node_3)
    {
      Relay[34] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (E_1 == Node_4)
    {
      Relay[35] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }

    //------------------------------------------ E2 ---------------------------------------
    if (E_2 == Node_1)
    {
      Relay[36] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (E_2 == Node_2)
    {
      Relay[37] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }
    if (E_2 == Node_3)
    {
      Relay[38] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (E_2 == Node_4)
    {
      Relay[39] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }

    //------------------------------------------ F1 ---------------------------------------
    if (F_1 == Node_1)
    {
      Relay[40] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (F_1 == Node_2)
    {
      Relay[41] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }
    if (F_1 == Node_3)
    {
      Relay[42] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (F_1 == Node_4)
    {
      Relay[43] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }

    //------------------------------------------ F2 ---------------------------------------
    if (F_2 == Node_1)
    {
      Relay[44] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (F_2 == Node_2)
    {
      Relay[45] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }
    if (F_2 == Node_3)
    {
      Relay[46] = 1;  // Switch on relay one which is connected to node-1 from first point of component
    }
    if (F_2 == Node_4)
    {
      Relay[47] = 1;  // // Switch on relay one which is connected to node-2 from first point of component
    }

    //--------------------------------------------------------------------------------------------------------

    Serial.println("Relay actuation list:");

    for (i = 0; i < 48; i++)
    {
      Serial.print(i);
      Serial.print(": ");
      Serial.println(Relay[i]);
    }

    //------------------------------------------- From somu ---------------------------------------


    if (Relay[0] == 1)
    {
      digitalWrite(OC1, HIGH);
      digitalWrite(IN1, LOW);
      Serial.println("RELAY_1");
    }
    if (Relay[1] == 1)
    {
      digitalWrite(OC1, HIGH);
      digitalWrite(IN2, LOW);
      Serial.println("RELAY_2");

    }
    if (Relay[2] == 1)
    {
      digitalWrite(OC1, HIGH);
      digitalWrite(IN3, LOW);
      Serial.println("RELAY_3");
    }
    if (Relay[3] == 1)
    {
      digitalWrite(OC1, HIGH);
      digitalWrite(IN4, LOW);
      Serial.println("RELAY_4");

    }
    if (Relay[4] == 1)
    {
      digitalWrite(OC1, HIGH);
      digitalWrite(IN5, LOW);
      Serial.println("RELAY_5");

    }
    if (Relay[5] == 1)
    {
      digitalWrite(OC1, HIGH);
      digitalWrite(IN6, LOW);
      Serial.println("RELAY_6");

    }
    if (Relay[6] == 1)
    {
      digitalWrite(OC1, HIGH);
      digitalWrite(IN7, LOW);
      Serial.println("RELAY_7");


    }
    if (Relay[7] == 1)
    {
      digitalWrite(OC1, HIGH);
      digitalWrite(IN8, LOW);
      Serial.println("RELAY_8");

    }

    digitalWrite(OC1, LOW);
    delay(20);
    ///////////////////// RELAY 2/////////
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, HIGH);
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, HIGH);

    // digitalWrite(OC2, LOW);
    if (Relay[8] == 1)
    {
      digitalWrite(OC2, HIGH);
      digitalWrite(IN1, LOW);
      Serial.println("RELAY_9");
    }
    if (Relay[9] == 1)
    {
      digitalWrite(OC2, HIGH);
      digitalWrite(IN2, LOW);
      Serial.println("RELAY_10");
    }
    if (Relay[10] == 1)
    {
      digitalWrite(OC2, HIGH);
      digitalWrite(IN3, LOW);
      Serial.println("RELAY_11");
    }
    if (Relay[11] == 1)
    {
      digitalWrite(OC2, HIGH);
      digitalWrite(IN4, LOW);
      Serial.println("RELAY_12");

    }
    if (Relay[12] == 1)
    {
      digitalWrite(OC2, HIGH);
      digitalWrite(IN5, LOW);
      Serial.println("RELAY_13");

    }
    if (Relay[13] == 1)
    {
      digitalWrite(OC2, HIGH);
      digitalWrite(IN6, LOW);
      Serial.println("RELAY_14");

    }
    if (Relay[14] == 1)
    {
      digitalWrite(OC2, HIGH);
      digitalWrite(IN7, LOW);
      Serial.println("RELAY_15");

    }
    if (Relay[15] == 1)
    {
      digitalWrite(OC2, HIGH);
      digitalWrite(IN8, LOW);
      Serial.println("RELAY_16");

    }
    // Switch case
    digitalWrite(OC2, LOW);
    delay(20);

    ///////////////////////////  Relay board 3/////////////////////////////////////////

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, HIGH);
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, HIGH);

    if (Relay[16] == 1)
    {
      digitalWrite(OC3, HIGH);
      digitalWrite(IN1, LOW);
      Serial.println("RELAY_17");
    }
    if (Relay[17] == 1)
    {
      digitalWrite(OC3, HIGH);
      digitalWrite(IN2, LOW);
      Serial.println("RELAY_18");
    }
    if (Relay[18] == 1)
    {
      digitalWrite(OC3, HIGH);
      digitalWrite(IN3, LOW);
      Serial.println("RELAY_19");
    }
    if (Relay[19] == 1)
    {
      digitalWrite(OC3, HIGH);
      digitalWrite(IN4, LOW);
      Serial.println("RELAY_20");

    }
    if (Relay[20] == 1)
    {
      digitalWrite(OC3, HIGH);
      digitalWrite(IN5, LOW);
      Serial.println("RELAY_21");

    }
    if (Relay[21] == 1)
    {
      digitalWrite(OC3, HIGH);
      digitalWrite(IN6, LOW);
      Serial.println("RELAY_22");
    }
    if (Relay[22] == 1)
    {
      digitalWrite(OC3, HIGH);
      digitalWrite(IN7, LOW);
      Serial.println("RELAY_23");

    }
    if (Relay[23] == 1)
    {
      digitalWrite(OC3, HIGH);
      digitalWrite(IN8, LOW);
      Serial.println("RELAY_24");

    }
    digitalWrite(OC3, LOW);
    delay(20);
    //////////////////////////  Relay board 4////////////////////////////////////////
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, HIGH);
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, HIGH);

    if (Relay[24] == 1)
    {
      digitalWrite(OC4, HIGH);
      digitalWrite(IN1, LOW);
      Serial.println("RELAY_25");
    }
    if (Relay[25] == 1)
    {
      digitalWrite(OC4, HIGH);
      digitalWrite(IN2, LOW);
      Serial.println("RELAY_26");
    }
    if (Relay[26] == 1)
    {
      digitalWrite(OC4, HIGH);
      digitalWrite(IN3, LOW);
      Serial.println("RELAY_27");
    }
    if (Relay[27] == 1)
    {
      digitalWrite(OC4, HIGH);
      digitalWrite(IN4, LOW);
      Serial.println("RELAY_28");

    }
    if (Relay[28] == 1)
    {
      digitalWrite(OC4, HIGH);
      digitalWrite(IN5, LOW);
      Serial.println("RELAY_29");

    }
    if (Relay[29] == 1)
    {
      digitalWrite(OC4, HIGH);
      digitalWrite(IN6, LOW);
      Serial.println("RELAY_30");

    }
    if (Relay[30] == 1)
    {
      digitalWrite(OC4, HIGH);
      digitalWrite(IN7, LOW);
      Serial.println("RELAY_31");

    }
    if (Relay[31] == 1)
    {
      digitalWrite(OC4, HIGH);
      digitalWrite(IN8, LOW);
      Serial.println("RELAY_32");

    }
    digitalWrite(OC4, LOW);
    delay(20);
    //////////////////////////  Relay board 5////////////////////////////////////////
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, HIGH);
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, HIGH);
    if (Relay[32] == 1)
    {
      digitalWrite(OC5, HIGH);
      digitalWrite(IN1, LOW);
      Serial.println("RELAY_33");
    }
    if (Relay[33] == 1)
    {
      digitalWrite(OC5, HIGH);
      digitalWrite(IN2, LOW);
      Serial.println("RELAY_34");
    }
    if (Relay[34] == 1)
    {
      digitalWrite(OC5, HIGH);
      digitalWrite(IN3, LOW);
      Serial.println("RELAY_35");
    }
    if (Relay[35] == 1)
    {
      digitalWrite(OC5, HIGH);
      digitalWrite(IN4, LOW);
      Serial.println("RELAY_36");

    }
    if (Relay[36] == 1)
    {
      digitalWrite(OC5, HIGH);
      digitalWrite(IN5, LOW);
      Serial.println("RELAY_37");

    }
    if (Relay[37] == 1)
    {
      digitalWrite(OC5, HIGH);
      digitalWrite(IN6, LOW);
      Serial.println("RELAY_38");

    }
    if (Relay[38] == 1)
    {
      digitalWrite(OC5, HIGH);
      digitalWrite(IN7, LOW);
      Serial.println("RELAY_39");

    }
    if (Relay[39] == 1)
    {
      digitalWrite(OC5, HIGH);
      digitalWrite(IN8, LOW);
      Serial.println("RELAY_40");

    }
    digitalWrite(OC5, LOW);
    delay(20);

    //////////////////////////  Relay board 6/////////////////////////////////////////
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, HIGH);
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, HIGH);

    if (Relay[40] == 1)
    {
      digitalWrite(OC6, HIGH);
      digitalWrite(IN1, LOW);
      Serial.println("RELAY_41");
    }
    if (Relay[41] == 1)
    {
      digitalWrite(OC6, HIGH);
      digitalWrite(IN2, LOW);
      Serial.println("RELAY_42");
    }
    if (Relay[42] == 1)
    {
      digitalWrite(OC6, HIGH);
      digitalWrite(IN3, LOW);
      Serial.println("RELAY_43");
    }
    if (Relay[43] == 1)
    {
      digitalWrite(OC6, HIGH);
      digitalWrite(IN4, LOW);
      Serial.println("RELAY_44");

    }
    if (Relay[44] == 1)
    {
      digitalWrite(OC6, HIGH);
      digitalWrite(IN5, LOW);
      Serial.println("RELAY_45");

    }
    if (Relay[45] == 1)
    {
      digitalWrite(OC6, HIGH);
      digitalWrite(IN6, LOW);
      Serial.println("RELAY_46");

    }
    if (Relay[46] == 1)
    {
      digitalWrite(OC6, HIGH);
      digitalWrite(IN7, LOW);
      Serial.println("RELAY_47");

    }
    if (Relay[47] == 1)
    {
      digitalWrite(OC6, HIGH);
      digitalWrite(IN8, LOW);
      Serial.println("RELAY_48");
    }
    digitalWrite(OC6, LOW);
    delay(20);

   // Relay[count_Relay] = 0;

    //---------------------------------------------- Till here somu code ---------------------
  }   // Single loop
} // Main loop
