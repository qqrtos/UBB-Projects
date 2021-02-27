<template>
<div>
	<h2 class="subtitle">{{model.heading}}</h2>

	<ValidationObserver ref="observer">
		<form @submit.prevent="submit" method="POST">
			<label for="register-fname">{{model.firstNameLabel}}</label>
			<div>
				<ValidationProvider rules="required" v-slot="{ errors }">
					<input id="First Name" v-model="FirstName" type="text">
					<div><span class="is-invalid">{{ errors[0] }}</span></div>
				</ValidationProvider>
			</div>

			<div>
				<label for="register-lname">{{model.lastNameLabel}}</label>
				<ValidationProvider rules="required" v-slot="{ errors }">
					<input id="Last Name" v-model="LastName" type="text">
					<div><span class="is-invalid">{{ errors[0] }}</span></div>
				</ValidationProvider>
			</div>

			<div>
				<label for="register-email">{{model.emailLabel}}</label>
				<ValidationProvider rules="required|email" v-slot="{ errors }">
					<input id="Email" v-model="Email" type="email">
					<div><span class="is-invalid">{{ errors[0] }}</span></div>
				</ValidationProvider>
			</div>

			<div>
				<label for="register-gender" class="col-xs-12">{{model.genderLabel}}</label>
				<ValidationProvider rules="required" v-slot="{ errors }">
					<input name="Gender" v-model="Gender" type="radio" value="Female"> <span class="gender-text">Female</span>
					<input name="Gender" v-model="Gender" type="radio" value="Male"> <span class="gender-text">Male</span>
					<div><span class="is-invalid">{{ errors[0] }}</span></div>
				</ValidationProvider>
			</div>

			<div>
				<label for="register-phonenumber">{{model.phoneNumberLabel}}</label>
				<ValidationProvider rules="required" v-slot="{ errors }">
					<input id="Phone Number" v-model="PhoneNumber" type="text">
					<div><span class="is-invalid">{{ errors[0] }}</span></div>
				</ValidationProvider>

			</div>

			<div>
				<label for="register-state">{{model.statesLabel}}</label>
				<ValidationProvider rules="required" v-slot="{ errors }">
					<select id="State" v-model="State" rules="required">
						<option v-for="option in model.statesList" :key="option" :value="option">
							{{option.name}}
						</option>
					</select>
					<div><span class="is-invalid">{{ errors[0] }}</span></div>
				</ValidationProvider>
			</div>

			<div>
				<label for="register-passwd">{{model.passwordabel}}</label>
				<ValidationProvider rules="required" ref="password" v-slot="{ errors }">
					<input id="Password" v-model="Password" type="password">
					<div><span class="is-invalid">{{ errors[0] }}</span></div>
				</ValidationProvider>
			</div>

			<div>
				<label for="register-confirmpasswd">{{model.confirmPasswordLabel}}</label>
				<ValidationProvider rules="required" ref="password" v-slot="{ errors }">
					<input id="Confirm Password" v-model="ConfirmPassword" type="password">
					<div><span class="is-invalid">{{ errors[0] }}</span></div>
				</ValidationProvider>
			</div>

			<button type="submit" class="btn btn-default" :disabled="errors">{{model.submitButtonText}}</button>

		</form>

		<p style="color:red;">{{inputErrors}}</p>

	</ValidationObserver>
</div>
</template>

<script>
	import $ from 'jquery'

	export default {
		data() {
			return {
				FirstName: '',
				LastName: '',
				PhoneNumber: '',
				Email: '',
				Gender: '',
				State: '',
				Password: '',
				ConfirmPassword: '',
				inputErrors: '',
				model: window.serverSideViewModel_Register
			}
		},

		methods: {
			handleRegister() {
                const self = this;
                $.post({
                    url: window.baseUrl + "/api/registerlogin/register",
                    data: {
                        email: this.Email,
                        password: this.Password,
                        confirmpassword: this.ConfirmPassword,
                        firstname: this.FirstName,
                        lastname: this.LastName,
                        phonenumber: this.PhoneNumber,
						gender: this.Gender,
						selectedstate: this.State
                    },
					success: function (data) {
						if (data.IsValid === false) {
                            self.inputErrors = data.ErrorMessage;
						}
						else {
                            window.location.href = '/'
                        }
                    },
                    error: function () { console.log("Error at login"); }
                });
			},
			async submit() {
                const isValid = await this.$refs.observer.validate();
                if (isValid) {
                    this.handleRegister();
                }
            }
        }
	}
</script>
