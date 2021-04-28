using System.Data;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Configuration;

namespace Assignment2 {
    public partial class Window : Form {
        private SqlConnection connection = new SqlConnection(@"Data Source=laptop-a2lrj4vg;Initial Catalog=et-music;Integrated Security=True");
        private DataSet dataSet = new DataSet();
        private SqlDataAdapter table1Adapter, table2Adapter;
        private SqlCommandBuilder command1, command2;
        private BindingSource table1Source = new BindingSource(), table2Source = new BindingSource();

        private string table1Name = ConfigurationManager.AppSettings["table1"];
        private string table2Name = ConfigurationManager.AppSettings["table2"];
        private string table1_FKName = ConfigurationManager.AppSettings["table1_FKColumnName"];
        private string table2_FKName = ConfigurationManager.AppSettings["table2_FKColumnName"];
        private string foreignKey = ConfigurationManager.AppSettings["foreignKey"];

        
        public Window() {
            InitializeComponent();
        }

        private void Window_Load(object sender, System.EventArgs e) {
            label1.Text = table1Name;
            label2.Text = table2Name;

            table1Adapter = new SqlDataAdapter($"SELECT * FROM {table1Name}", connection);
            table2Adapter = new SqlDataAdapter($"SELECT * FROM {table2Name}", connection);
            command1 = new SqlCommandBuilder(table1Adapter);
            command2 = new SqlCommandBuilder(table2Adapter);

            table1Adapter.Fill(dataSet, table1Name);
            table2Adapter.Fill(dataSet, table2Name);

            DataRelation relationBetweenData = new DataRelation(
                    foreignKey,
                    dataSet.Tables[table2Name].Columns[table2_FKName],
                    dataSet.Tables[table1Name].Columns[table1_FKName]
                );
            dataSet.Relations.Add(relationBetweenData);

            table2Source.DataSource = dataSet;
            table2Source.DataMember = table2Name;

            table1Source.DataSource = table2Source;
            table1Source.DataMember = foreignKey;

            dataGridView1.DataSource = table1Source;
            dataGridView2.DataSource = table2Source;
        }

        private void persistButton_Click(object sender, System.EventArgs e) {
            table1Adapter.Update(dataSet, table1Name);
            table2Adapter.Update(dataSet, table2Name);
        }
    }
}
