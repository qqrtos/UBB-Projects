<template>
    <div id="minicart" @mouseover="Show()" @mouseout="NotShow()">
        <div class="minicart-group">
            <i class="fas fa-shopping-cart fa-2x"></i> <span v-show="btn == 0">{{nr}} items</span>
            <a href="/en/shoppingcartpage/"><button class="quick-checkout-btn" v-show="btn == 1 ">Quick Checkout </button></a>
        </div>
    </div>
</template>

<script>
    import $ from 'jquery';
    import { EventBus } from '../event-bus.js';

    export default {
        data() {
            return {
                quantity: null,
                btn: false,
            };
        },
        computed: {
            nr() {
                return this.quantity;
            },
        },
        methods: {
            Show: function () {
                this.btn = true
            },
            NotShow: function () {
                this.btn = false
            },
            UpdateQuantity(incomingQuantity) {
                if (this.quantity != null)
                    this.quantity += incomingQuantity;
                else
                    this.quantity = incomingQuantity;
            }
        },

        created() {
            const self = this;
            $.get({
                url: '/api/ShoppingCartApi/getquantity',
                success: function (data) {
                    console.log('Minicart initialize: ' + data);
                    self.quantity = data;
                },
                error: function () {
                    console.log('Error on minicart init');
                }
            });
        },

        mounted() {
            EventBus.$on('i-changed', quantity => {
                this.UpdateQuantity(quantity);
            });
        }
    }
</script>
