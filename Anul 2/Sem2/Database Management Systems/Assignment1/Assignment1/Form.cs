using System;
using System.Data;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace Assignment1 {
    public partial class Form : System.Windows.Forms.Form {
        SqlConnection Connection = new SqlConnection("Data Source=laptop-a2lrj4vg;Initial Catalog=et-music;Integrated Security=True");
        DataSet DataSet = new DataSet();
        BindingSource SongsSource = new BindingSource(), AlbumsSource = new BindingSource();
        SqlDataAdapter SongsAdapter, AlbumsAdapter;

        public Form() {
            InitializeComponent();
        }


        private void Form_Load(object sender, EventArgs e) {
            SongsAdapter = new SqlDataAdapter("SELECT * FROM Songs", Connection);
            AlbumsAdapter = new SqlDataAdapter("SELECT * FROM Albums", Connection);

            AlbumsAdapter.Fill(DataSet, "Albums");
            AlbumsSource.DataSource = DataSet;
            AlbumsSource.DataMember = "Albums";

            SongsAdapter.Fill(DataSet, "Songs");
            DataRelation relationBetweenData = new DataRelation(
                    "FK__Songs_Albums",
                    DataSet.Tables["Albums"].Columns["Id"],
                    DataSet.Tables["Songs"].Columns["AlbumId"]
                );
            DataSet.Relations.Add(relationBetweenData);

            SongsSource.DataSource = AlbumsSource;
            SongsSource.DataMember = "FK__Songs_Albums";

            AlbumsDataGridView.DataSource = AlbumsSource;
            SongsDataGridView.DataSource = SongsSource;
        }

        private void PersistChangesButton_Click(object sender, EventArgs e) {
            SongsAdapter.Update(DataSet, "Songs");
            //AlbumsAdapter.Update(DataSet, "Albums");
        }
    }
}
