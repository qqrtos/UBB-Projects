<template>
<div>
    <h2 class="subtitle">{{model.heading}}</h2>

    <ValidationObserver ref="observer">
        <form @submit.prevent="submit" method="POST">
            <div>
                <label for="login-email" class="col-xs-12">{{model.emailLabel}}</label>
                <ValidationProvider rules="required|email" v-slot="{ errors }">
                    <input id="Login Email" v-model="Email" type="email" :placeholder="[[ model.emailPlaceholder ]]">
                    <div><span class="is-invalid">{{ errors[0] }}</span></div>
                </ValidationProvider>
            </div>

            <div>
                <label for="login-passwd" class="col-xs-12">{{model.passwordLabel}}</label>
                <ValidationProvider rules="required" ref="password" v-slot="{ errors }">
                    <input id="Login Password" v-model="Password" type="password"  placeholder="• • • • • • • •">
                    <div><span class="is-invalid">{{ errors[0] }}</span></div>
                </ValidationProvider>
            </div>

            <button type="submit" class="btn btn-default" :disabled="errors">{{model.submitButtonText}}</button>

        </form>
    </ValidationObserver>

    <p style="color:red;">{{inputErrors}}</p>
</div>
</template>

<script>
    import $ from 'jquery'

    export default {
        data() {
            return {
                Email: '',
                Password: '',
                inputErrors: '',
                model: window.serverSideViewModel_Login
            }
        },
        methods: {
            handleLogin() {
                const self = this;
                $.post({
                    url: window.baseUrl + "api/registerlogin/login",
                    data: {
                        email: self.Email,
                        password: self.Password
                    },
                    success: function (data) {
                        if (data.IsValid === false) {
                            self.inputErrors = data.ErrorMessage;
                        }
                        else {
                            window.location.href = '/'
                        }
                    },
                    error: function () { console.log('Error at Login API call.'); }
                });
            },
            async submit() {
                const isValid = await this.$refs.observer.validate();
                if (isValid) {
                    this.handleLogin();
                }
            }
        }
    }
</script>
