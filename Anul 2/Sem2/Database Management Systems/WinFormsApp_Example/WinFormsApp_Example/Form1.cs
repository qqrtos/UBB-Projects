using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace WinFormsApp_Example {
    public partial class Form1 : Form {
        private SqlConnection connection;
        private DataSet dataSet = new DataSet();
        private SqlDataAdapter shipsAdaptor, piratesAdaptor;
        private SqlCommandBuilder commandBuilder;
        private BindingSource shipsSource = new BindingSource(), piratesSource = new BindingSource();

        public Form1() {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e) {
            connection = new SqlConnection("Data Source=laptop-a2lrj4vg;Initial Catalog=Pirates;Integrated Security=True");

            shipsAdaptor = new SqlDataAdapter("select * from ships", connection);
            piratesAdaptor = new SqlDataAdapter("select * from pirates", connection);

            commandBuilder = new SqlCommandBuilder(shipsAdaptor);

            shipsAdaptor.Fill(dataSet, "ships");
            piratesAdaptor.Fill(dataSet, "pirates");

            DataRelation relation = new DataRelation("FK_Pirates_Ships", dataSet.Tables["ships"].Columns["ShipID"], dataSet.Tables["pirates"].Columns["ShipID"]);
            dataSet.Relations.Add(relation);

            shipsSource.DataSource = dataSet;
            shipsSource.DataMember = "ships";

            piratesSource.DataSource = dataSet;
            piratesSource.DataMember = "FK_Pirates_Ships";

            shipsGridView.DataSource = shipsSource;
            piratesGridView.DataSource = piratesSource;
        }

        private void buttonSave_Click(object sender, EventArgs e) {

        }
       
    }
}
