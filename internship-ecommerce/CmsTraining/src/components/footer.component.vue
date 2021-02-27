<template>
    <div>
        <footer>
            <h3 v-if="isUserSubscribed"> Thank you for subscribing! </h3>
            <div v-else class="input-group mb-3 collapse text-white d-lg-flex" id="three" data-parent="#accordion">

                <ValidationObserver ref="observer">
                    <div class="together">
                        <ValidationProvider rules="required|email" v-slot="{ errors }">
                            <input id="email" autocomplete="off" v-model="MailInput" type="email" placeholder="Your email here">
                            <div><span class="is-invalid">{{ errors[0] }}</span></div>
                        </ValidationProvider>

                        <!--<input :value="mail" class="input-style" placeholder="Your email address" type="email" />-->
                        <div class="input-group-append">
                            <button class="btn-outline-secondary btn-footer" value="Submit!" :disabled="errors" @click="Submit">
                                <p class="submit-btn-text">Submit</p>
                            </button>
                        </div>
                    </div>

                </ValidationObserver>

                <p>&copy; Subscribe to our newsletter.</p>

            </div>
        </footer>
    </div>
</template>

<style scoped>
    input:focus {
        outline: none;
    }
</style>

<script>
    import $ from 'jquery'

    export default {
        data() {
            return {
                MailInput: '',
                isUserSubscribed: false,
            };
        },
        methods: {
            CheckSubscription() {
                const self = this;
                $.ajax({
                    url: window.baseUrl + "api/apifooter/HasSubscribedCookie",
                    type: "get",
                    success: function (data) {
                        if (data === true) {
                            self.isUserSubscribed = true;
                        }
                        else {
                            self.isUserSubscribed = false;
                        }
                    },
                    error: function () { console.log("Error on footer init.") }
                });
            },

            SubmitApiCall() {
                let mail = this.MailInput;
                $.ajax({
                    url: window.baseUrl + "api/apifooter/SubmitSubscription",
                    type: "get",
                    data: {
                        mail: mail
                    },
                    error: function () { console.log("Error on submit"); }
                }).then(() => { this.CheckSubscription(); });
            },

            async Submit() {
                const isValid = await this.$refs.observer.validate();
                if (isValid) {
                    this.SubmitApiCall();
                }
            }
        },

        created() {
            this.CheckSubscription();
        }
    }
</script>
