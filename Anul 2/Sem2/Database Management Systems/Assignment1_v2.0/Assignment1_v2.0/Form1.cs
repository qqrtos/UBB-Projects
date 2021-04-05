using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace Assignment1_v2._0 {
    public partial class Form1 : Form {
        SqlConnection Connection = new SqlConnection("Data Source=laptop-a2lrj4vg;Initial Catalog=et-music;Integrated Security=True");
        DataSet DataSet = new DataSet();
        BindingSource SongsSource = new BindingSource(), AlbumsSource = new BindingSource();
        SqlDataAdapter SongsAdapter, AlbumsAdapter;
        SqlCommandBuilder SongsCommandBuilder, AlbumsCommandBuilder;


        public Form1() {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e) {
            SongsAdapter = new SqlDataAdapter("SELECT * FROM Songs", Connection);
            AlbumsAdapter = new SqlDataAdapter("SELECT * FROM Albums", Connection);
            SongsCommandBuilder = new SqlCommandBuilder(SongsAdapter);
            AlbumsCommandBuilder = new SqlCommandBuilder(AlbumsAdapter);

            SongsAdapter.Fill(DataSet, "Songs");
            AlbumsAdapter.Fill(DataSet, "Albums");

            DataRelation relationBetweenData = new DataRelation(
                    "FK__Songs_Albums",
                    DataSet.Tables["Albums"].Columns["Id"],
                    DataSet.Tables["Songs"].Columns["AlbumId"]
                );
            DataSet.Relations.Add(relationBetweenData);

            AlbumsSource.DataSource = DataSet;
            AlbumsSource.DataMember = "Albums";

            SongsSource.DataSource = AlbumsSource;
            SongsSource.DataMember = "FK__Songs_Albums";

            AlbumsDataGridView.DataSource = AlbumsSource;
            SongsDataGridView.DataSource = SongsSource;
        }

        private void PersistChangesButton_Click(object sender, EventArgs e) {
            /*for (int i = 0; i < SongsDataGridView.Rows.Count; ++i) {
                string query = "DELETE FROM Songs WHERE Id = @sid";

                SqlCommand command = new SqlCommand(query, Connection);
                var sid = SongsDataGridView.Rows[i].Cells[0].Value.ToString();
                command.Parameters.AddWithValue("@sid", sid);

                command.ExecuteNonQuery();
            }*/

            SongsAdapter.Update(DataSet, "Songs");
            AlbumsAdapter.Update(DataSet, "Albums");
        }
    }
}
