function handleLogout() {
    $.post({
        url: window.baseUrl + "api/registerlogin/logout",
        success: function () {
            window.location.href = '/'
        }
    });
}